/*
 * Copyright (c) 2020 Safecility.com
 * Author: tad@safecility.com
 */

#include <zephyr.h>
#include <device.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <power/reboot.h>

#include <bsd.h>
#include <modem/lte_lc.h>
#include <modem/modem_info.h>

#include <nrf_socket.h>
#include <net/socket.h>
#include <net/mqtt.h>

#include <date_time.h>
#include <gcloud.h>
#include <cJSON.h>
#include <env_sensors/env_sensors.h>
#include <watchdog/watchdog.h>

#define CONFIG_APPLICATION_WORKQUEUE_PRIORITY 7

#define DATA_ARRAY_SIZE 240 
#define THREAD_INDEX DATA_ARRAY_SIZE-2 //CANDO: test n-1 to minimise tls session data usage 
#define REBOOT_TIMEOUT 30000 //CANDO: reduce timeout as above
#define EXCLUDE 999

/* Register main module log */
LOG_MODULE_REGISTER(google_mqtt, CONFIG_GCLOUD_LOG_LEVEL);

/* Stack definition for application */
static K_THREAD_STACK_DEFINE(app_stack_area, 8192);
static K_THREAD_STACK_DEFINE(env_sens_stack_area, 8192);
static K_THREAD_STACK_DEFINE(data_ag_stack_area, 8192);
static K_THREAD_STACK_DEFINE(gc_stack_area, 4096);
static K_THREAD_STACK_DEFINE(ntp_stack_area, 512);
static K_THREAD_STACK_DEFINE(wdt_stack_area, 512);

/* Work Queues */
static struct k_work_q env_sens_q;
static struct k_work_q app_work_q;

/* Threads */
static struct k_thread ntp_thread;
static struct k_thread data_ag_thread;
static struct k_thread app_thread;
static struct k_thread gc_thread;

k_tid_t ntp_tid;
k_tid_t d_ag_tid;
k_tid_t app_tid;
k_tid_t gc_tid;

/* Normal env data */
struct env_data_t {
    s32_t t;
    s32_t h;
    s32_t p;
    s32_t q;
} env_d;

/* Aggregated env data type */
struct ag_data_t {
    s32_t max;
    s32_t min;
    s32_t avg;
} ag_d;

/* Packed struct */
struct pac_data_t {
    struct ag_data_t ag_temp;
    struct ag_data_t ag_humi;
    struct ag_data_t ag_pres;
    struct ag_data_t ag_qual;
} p_d;

struct m_info_t {
    char cid[30];
    char tac[30];
    char rssi[30];
    char apn[60];
    char fwv[60];
    uint16_t vltg;
    uint16_t temp;
};

/* Mailbox */
struct k_mbox env_d_mailbox;

/* Initialise Message Queues */
char __aligned(4) (env_msgq_buffer[10 * 36]);
struct k_msgq env_msg_q;

/* Global Flags */
volatile bool got_ntp = false;

/* Forward declarations of functions */
static void store_modem_configuration(void);
static void env_data_ready(void);

/*
* bool if_qual - exclude readings of 999 from calculations
*/

/* Get average value of array */
s32_t calculate_avg_val(s32_t a[], s32_t sz, bool is_qual)
{
    s32_t sum = 0;
    s32_t excl_cnt = 0;

    for(s32_t i=0; i<sz; i++) {
        if (!is_qual) {
            sum += a[i];
        } else if (is_qual && a[i] != EXCLUDE) {
            sum += a[i];
        } else {
            excl_cnt += 1;
        }
    }
    return (sum/(sz-excl_cnt));
}

/* Get min value of array */
s32_t calculate_min_val(s32_t a[],s32_t sz, bool is_qual)
{
    s32_t min, i;
    s32_t excl_cnt = 0;

 	min=a[0];
 	
    for(i=1; i<sz; i++) {
        if(min>a[i])
        min=a[i];   
    }
    return min;
}

/* Get max value of array */
s32_t calculate_max_val(s32_t a[],s32_t sz, bool is_qual)
{
 	s32_t max,i;
    s32_t excl_cnt = 0;
    
 	max=a[0];

    for(i=1; i<sz; i++) {
        if(max<a[i])
        max=a[i];       
    }
    return max;
}


/* Handlers */
void button_handler(u32_t button_state, u32_t has_changed)
{
    // printk("Button event: %x  %x\n", button_state, has_changed);
    // if ( (has_changed & 0x01) && (button_state & 0x01) ) {
    //     store_modem_configuration();
    // }
}

/**@brief Handler for when receiving data from Google Cloud */ 
void received_config_handler(const struct mqtt_publish_message *message) {

	cJSON * data_json = cJSON_Parse(message->payload.data);

    // LOG_INF("%s\n",cJSON_Print(data_json));

	cJSON_Delete(data_json);
}


/**@brief Configures modem to provide LTE link. Blocks until link is
 * successfully established
 */
static void modem_configure(void)
{
    if (IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT)) {
        /* Do nothing, modem is already turned on and connected */
    } else {
        int err;

        LOG_INF("Establishing LTE link\n");
        err = lte_lc_init_and_connect();
        __ASSERT(err == 0, "LTE link could not be established. Rebooting\n");
    }
}

/**@brief Configures AT Command interface to the modem link. */
static void at_configure(void)
{
	int err;
	err = at_notif_init();
	__ASSERT(err == 0, "AT Notify could not be initialized.");
	err = at_cmd_init();
	__ASSERT(err == 0, "AT CMD could not be established.");
}

/**@brief Soft boots modem to store current values to NVM */
void store_modem_configuration(void)
{
    int err;

    LOG_INF("Storing modem configuration\n");
    err = lte_lc_power_off();
    if (err) {
        LOG_INF("Fail turning off modem: %d\n", err);
    }
    LOG_INF("Modem offline, turning back on\n");

    err = lte_lc_normal();
    if (err) {
        LOG_INF("Fail turning on modem: %d\n", err);
    }
    LOG_INF("Done\n");
}


/**@brief Return modem information */
void get_modem_info(struct m_info_t *info) 
{
    LOG_INF("Getting modem info\n");
    modem_info_string_get(MODEM_INFO_CELLID, info->cid, sizeof(info->cid));

    modem_info_string_get(MODEM_INFO_AREA_CODE, info->tac, sizeof(info->tac));

    modem_info_string_get(MODEM_INFO_RSRP, info->rssi, sizeof(info->rssi));

    modem_info_string_get(MODEM_INFO_APN, info->apn, sizeof(info->apn));

    modem_info_string_get(MODEM_INFO_FW_VERSION, info->fwv, sizeof(info->fwv));

	modem_info_short_get(MODEM_INFO_BATTERY, &info->vltg);

    modem_info_short_get(MODEM_INFO_TEMP, &info->temp);
}

/**@brief Store sensor data and process once full and
* initialises Google cloud thread
*/
void process_env_data(void) 
{
    struct env_data_t d_temp;

    s32_t tempArray [DATA_ARRAY_SIZE];
    s32_t humiArray [DATA_ARRAY_SIZE];
    s32_t presArray [DATA_ARRAY_SIZE];
    s32_t qualArray [DATA_ARRAY_SIZE];

    struct k_mbox_msg send_env_msg;
    struct pac_data_t pac_data;

    u32_t buffer_bytes_used;
    u32_t run_count = 0;
    bool thread_started = false;

    int err;

    while (true)
    {
        /* Get data and store - for size of array */
        for (int i = 0; i < DATA_ARRAY_SIZE; i++)
        {
            /* pull data from queue */
            LOG_DBG("Getting environmental data: [%d] of [%d]", i, DATA_ARRAY_SIZE);
            k_msgq_get(&env_msg_q, &d_temp, K_FOREVER);

            tempArray[i] = (s32_t)d_temp.t;
            humiArray[i] = (s32_t)d_temp.h;
            presArray[i] = (s32_t)d_temp.p;

            /* guard qual array from spurious readings 
            * can array be dynamically resized?
            */
            if (iaq_accuracy == BSEC_CALIBRATED) {
                qualArray[i] = (s32_t)d_temp.q; // fill array with reading
            } else {
               qualArray[i] = NULL; //TODO: anything over 500 not valid iaq reading but valid pres?
            }

            /* Increment data getter counter */
            run_count +=1;
            LOG_INF("Run Count: [%d]\n", run_count);

            if (!thread_started) {
                LOG_INF("[%d] samples to Google thread entry\n", ((THREAD_INDEX) - run_count));
            }

            /* If sufficient data collected start google thread */
            if ((run_count == (THREAD_INDEX)) && (!thread_started))
            {
                thread_started = true;
                run_count = 0;
                /* Provision Google Cloud Security Creds */
                LOG_INF("Provisioning\n");
                err = gcloud_provision();
                if (err) {
                    LOG_ERR("Failed to provision: %d\n", err);
                    /* Reboot */
                    sys_reboot(0); //TODO: Handle error
                } else {
                    LOG_INF("Provisioning complete\n");
                }

                /* Connect to Google Cloud */
                LOG_INF("Connecting to Google Cloud\n");
                err = gcloud_connect(received_config_handler);
                if (err) {
                    LOG_ERR("Failed to connect to Google Cloud, error: %d\n", err);
                    /* Reboot */
                    sys_reboot(0); //TODO: Handle error
                } else {
                    LOG_INF("Connected to Google Cloud\n");
                }
            }
        }

        /* Calculate data mean */
        LOG_INF("Calculating environmental data type avg");
        pac_data.ag_temp.avg = calculate_avg_val(tempArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_humi.avg = calculate_avg_val(humiArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_pres.avg = calculate_avg_val(presArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_qual.avg = calculate_avg_val(qualArray, DATA_ARRAY_SIZE, true);
        LOG_INF("Mean temp: %d", (s32_t)pac_data.ag_temp.avg);
        LOG_INF("Mean humi: %d", (s32_t)pac_data.ag_humi.avg);
        LOG_INF("Mean pres: %d", (s32_t)pac_data.ag_pres.avg);
        LOG_INF("Mean qual: %d", (s32_t)pac_data.ag_qual.avg);

        /* Calculate data min */
        LOG_INF("Calculating environmental data type min");
        pac_data.ag_temp.min = calculate_min_val(tempArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_humi.min = calculate_min_val(humiArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_pres.min = calculate_min_val(presArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_qual.min = calculate_min_val(qualArray, DATA_ARRAY_SIZE, true);
        LOG_INF("Min temp: %d", (s32_t)pac_data.ag_temp.min);
        LOG_INF("Min humi: %d", (s32_t)pac_data.ag_humi.min);
        LOG_INF("Min pres: %d", (s32_t)pac_data.ag_pres.min);
        LOG_INF("Min qual: %d", (s32_t)pac_data.ag_qual.min);

        /* Calculate data max */
        LOG_INF("Calculating environmental data type max");
        pac_data.ag_temp.max = calculate_max_val(tempArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_humi.max = calculate_max_val(humiArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_pres.max = calculate_max_val(presArray, DATA_ARRAY_SIZE, false);
        pac_data.ag_qual.max = calculate_max_val(qualArray, DATA_ARRAY_SIZE, true);
        LOG_INF("Max temp: %d", (s32_t)pac_data.ag_temp.max);
        LOG_INF("Max humi: %d", (s32_t)pac_data.ag_humi.max);
        LOG_INF("Max pres: %d", (s32_t)pac_data.ag_pres.max);
        LOG_INF("Max qual: %d", (s32_t)pac_data.ag_qual.max);

        /* Callback to Google Cloud Thread */
        LOG_INF("Sending data to google iot thread");
        
        buffer_bytes_used = sizeof(p_d);   //TODO: test that size is correct

        /* prepare to send message */
        send_env_msg.info = buffer_bytes_used;
        send_env_msg.size = buffer_bytes_used;
        send_env_msg.tx_data = &pac_data;
        send_env_msg.tx_block.data = NULL;
        send_env_msg.tx_target_thread = K_ANY;

        /* send message and wait until a consumer receives it */
        k_mbox_put(&env_d_mailbox, &send_env_msg, K_FOREVER);

        /* verify that message data was fully received */
        if (send_env_msg.size < buffer_bytes_used) {
            LOG_DBG("env msg RXer only had room for [%d] bytes", send_env_msg.info);
        }

    }
}

/**@brief Environmental sensor data ready callback */
static void env_data_ready(void)
{
    env_sensor_data_t temp, humi, pres, qual;
    struct env_data_t env_data;

    LOG_INF("env sens data ready");

    /*
    Get sensor data and push to queue
    */
    if (! env_sensors_get_temperature(&temp)) {

        (env_data.t) = (s32_t)temp.value;
    }
    if (! env_sensors_get_humidity(&humi)) {

        (env_data.h) = (s32_t)humi.value;
    }
    if (! env_sensors_get_pressure(&pres)) {

        (env_data.p) = (s32_t)pres.value;
    }
    if (! env_sensors_get_air_quality(&qual)) {

        (env_data.q) = (s32_t)qual.value;
    }

    /* send data to main thread */
    k_msgq_put(&env_msg_q, &env_data, K_NO_WAIT); //TODO: Is flushing the desired behaviour?
}


/**@brief Initializes environmental sensor object */
void init_env_sensor(void)
{
    int err;

    LOG_INF("Sensor workqueue started\n");
	k_work_q_start(&env_sens_q, env_sens_stack_area,
		       K_THREAD_STACK_SIZEOF(env_sens_stack_area),
		       CONFIG_APPLICATION_WORKQUEUE_PRIORITY);

    LOG_INF("Initializing environmental sensor\n");
    err = env_sensors_init_and_start(&env_sens_q, env_data_ready);
    if (err) {
        LOG_INF("environmental sensor initialization failed [%d]\n", err);
    }
    else {
        LOG_INF("environmental sensor initialized\n");
    }
}


/**@brief Poll for ntp timestamp */
int ntp_poll(void)
{
    s64_t date_time_stamp;

    while (date_time_now(&date_time_stamp) != 0)
    {
        LOG_ERR("Couldn't get time\n");
        k_sleep(K_MSEC(10000));
    }
    got_ntp = true;
    return 0;
}


/**@brief Main Processing Thread */
void app_gc_iot(void)
{
    bool sent_once = false;

    struct pac_data_t pac_data;
    struct m_info_t info;

    struct k_mbox_msg env_d_recv_msg;

    /* Block until  */
    while (!got_ntp) 
    {   
        LOG_INF("Waiting on Modem Time\n");
        k_sleep(K_MSEC(10000));
    }
    
    while(true) {
        
        /* prepare to receive message */
        env_d_recv_msg.info = 256;
        env_d_recv_msg.size = sizeof(pac_data);
        env_d_recv_msg.rx_source_thread = K_ANY; //TODO: Get producer thread id

        /* get data from mailbox - blocking */
        LOG_DBG("App thread waiting for data from producer\n");
        k_mbox_get(&env_d_mailbox, &env_d_recv_msg, &pac_data, K_FOREVER);

        /* verify that message data was fully received */
        if (env_d_recv_msg.info != env_d_recv_msg.size) {
            LOG_INF("Sender tried to send [%d] bytes\n", env_d_recv_msg.info);
        } else {
            LOG_INF("Received k_mbox\n");
        }

        /* Get modem information */
        get_modem_info(&info);
        printk("CID: [%s]\n", info.cid);
        printk("TAC: [%s]\n", info.tac);
        printk("RSSI: [%s]\n", info.rssi);
        printk("APN: [%s]\n", info.apn);
        printk("FWV: [%s]\n", info.fwv);
        LOG_INF("Voltage: [%d]\n", info.vltg);
        LOG_INF("Temp: [%d]\n", info.temp);
    
        /* Create cJSON object */
        cJSON * envSensObj = cJSON_CreateObject();

        const char * jCidString = "cid";
        const char * jTacString = "tac";
        const char * jRssiString = "rssi";
        const char * jApnString = "apn";
        const char * jFwvString = "fwv";
        const char * jVltgString = "vltg";
        const char * jTempString = "itemp";
        cJSON *jCid = NULL;
        cJSON *jTac = NULL;
        cJSON *jRssi = NULL;
        cJSON *jApn = NULL;
        cJSON *jFwv = NULL;
        cJSON *jVltg = NULL;
        cJSON *jTemp = NULL;

        /* Create cJSON strings */
        const char * jTempMaxString = "tempMax";
        const char * jHumiMaxString = "humiMax";
        const char * jPresMaxString = "presMax";
        const char * jQualMaxString = "qualMax";
        cJSON *jTempMax = NULL;
        cJSON *jHumiMax = NULL;
        cJSON *jPresMax = NULL;
        cJSON *jQualMax = NULL;

        const char * jTempMinString = "tempMin";
        const char * jHumiMinString = "humiMin";
        const char * jPresMinString = "presMin";
        const char * jQualMinString = "qualMin";
        cJSON *jTempMin = NULL;
        cJSON *jHumiMin = NULL;
        cJSON *jPresMin = NULL;
        cJSON *jQualMin = NULL;
        
        const char * jTempAvgString = "tempAvg";
        const char * jHumiAvgString = "humiAvg";
        const char * jPresAvgString = "presAvg";
        const char * jQualAvgString = "qualAvg";
        cJSON *jTempAvg = NULL;
        cJSON *jHumiAvg = NULL;
        cJSON *jPresAvg = NULL;
        cJSON *jQualAvg = NULL;

        const char * jSampSzString = "sampleSz";
        const char * jSampFrqString = "sampleFrq";
        cJSON *jSampSz = NULL;
        cJSON *jSampFrq = NULL;

        /* Initialise empty string */
        char * JSONEnvString = NULL;

        /* create cJSON items */
        jTempMax = cJSON_CreateNumber((s32_t)pac_data.ag_temp.max);
        jTempMin = cJSON_CreateNumber((s32_t)pac_data.ag_temp.min);
        jTempAvg = cJSON_CreateNumber((s32_t)pac_data.ag_temp.avg);

        jHumiMax = cJSON_CreateNumber((s32_t)pac_data.ag_humi.max);
        jHumiMin = cJSON_CreateNumber((s32_t)pac_data.ag_humi.min);
        jHumiAvg = cJSON_CreateNumber((s32_t)pac_data.ag_humi.avg);

        jPresMax = cJSON_CreateNumber((s32_t)pac_data.ag_pres.max);
        jPresMin = cJSON_CreateNumber((s32_t)pac_data.ag_pres.min);
        jPresAvg = cJSON_CreateNumber((s32_t)pac_data.ag_pres.avg);

        jQualMax = cJSON_CreateNumber((s32_t)pac_data.ag_qual.max);
        jQualMin = cJSON_CreateNumber((s32_t)pac_data.ag_qual.min);
        jQualAvg = cJSON_CreateNumber((s32_t)pac_data.ag_qual.avg);

        jSampSz = cJSON_CreateNumber(DATA_ARRAY_SIZE);
        jSampFrq = cJSON_CreateNumber(33);

        jCid = cJSON_CreateString((const char*)info.cid);
        jTac = cJSON_CreateString((const char*)info.tac);
        jRssi = cJSON_CreateString((const char*)info.rssi);
        jApn = cJSON_CreateString((const char*)info.apn);
        jFwv = cJSON_CreateString((const char*)info.fwv);
        jVltg = cJSON_CreateNumber((u16_t)info.vltg);
        jTemp = cJSON_CreateNumber((u16_t)info.temp);

        /* Add cJSON items to object */
        cJSON_AddItemToObject(envSensObj, jTempMaxString, jTempMax);
        cJSON_AddItemToObject(envSensObj, jHumiMaxString, jHumiMax);
        cJSON_AddItemToObject(envSensObj, jPresMaxString, jPresMax);
        cJSON_AddItemToObject(envSensObj, jQualMaxString, jQualMax);

        cJSON_AddItemToObject(envSensObj, jTempMinString, jTempMin);
        cJSON_AddItemToObject(envSensObj, jHumiMinString, jHumiMin);
        cJSON_AddItemToObject(envSensObj, jPresMinString, jPresMin);
        cJSON_AddItemToObject(envSensObj, jQualMinString, jQualMin);

        cJSON_AddItemToObject(envSensObj, jTempAvgString, jTempAvg);
        cJSON_AddItemToObject(envSensObj, jHumiAvgString, jHumiAvg);
        cJSON_AddItemToObject(envSensObj, jPresAvgString, jPresAvg);
        cJSON_AddItemToObject(envSensObj, jQualAvgString, jQualAvg);

        cJSON_AddItemToObject(envSensObj, jSampSzString, jSampSz);
        cJSON_AddItemToObject(envSensObj, jSampFrqString, jSampFrq);

        cJSON_AddItemToObject(envSensObj, jCidString, jCid);
        cJSON_AddItemToObject(envSensObj, jTacString, jTac);
        cJSON_AddItemToObject(envSensObj, jRssiString, jRssi);
        cJSON_AddItemToObject(envSensObj, jApnString, jApn);
        cJSON_AddItemToObject(envSensObj, jFwvString, jFwv);
        cJSON_AddItemToObject(envSensObj, jVltgString, jVltg);
        cJSON_AddItemToObject(envSensObj, jTempString, jTemp);


        /* Create JSON string from object */
        JSONEnvString = cJSON_Print(envSensObj);
        if (JSONEnvString == NULL) {
            LOG_DBG("Failed to print envSensObj\n");
        }

        /* Send JSON data */
        LOG_INF("Sending JSON data\n");
	    int pub_success = gcloud_publish(JSONEnvString, strlens(JSONEnvString), MQTT_QOS_0_AT_MOST_ONCE);
        LOG_INF("Sent JSON data with code: [%d]\n", pub_success);
        if (pub_success != 0) {
            LOG_INF("JSON data Publish failed\n");
        }

        /* Cleanup JSON obj */
        cJSON_Delete(envSensObj);

        /* Reboot */
        LOG_INF("Rebooting in [%d] seconds\n", REBOOT_TIMEOUT/1000);
        k_sleep(K_MSEC(REBOOT_TIMEOUT));
        LOG_INF("Rebooting\n");
        sys_reboot(0);
    }
    /* Is it correct to disconnect? */
    gcloud_disconnect();
    sys_reboot(0);
    
}

/**@brief Main Processing Thread */
void main(void)
{

    LOG_INF("Google Cloud env sensor app started");

	k_work_q_start(&app_work_q, wdt_stack_area,
		       K_THREAD_STACK_SIZEOF(wdt_stack_area),
		       CONFIG_APPLICATION_WORKQUEUE_PRIORITY);
	if (IS_ENABLED(CONFIG_WATCHDOG)) {
		watchdog_init_and_start(&app_work_q);
	}

	LOG_INF("Initializing modem\n");
    modem_configure();

    LOG_INF("Initializing modem info\n");
    modem_info_init();

    LOG_INF("Initializing environmental sensor\n");
    init_env_sensor();

    LOG_INF("Initializing bsec data message queue\n");
    k_msgq_init(&env_msg_q, env_msgq_buffer, sizeof(env_d), 10);

    LOG_INF("Initializing aggregated data mailbox\n");
    k_mbox_init(&env_d_mailbox);

    /* Start data aggregation thread */
    d_ag_tid = k_thread_create(&data_ag_thread, data_ag_stack_area, K_THREAD_STACK_SIZEOF(data_ag_stack_area),
        (k_thread_entry_t)process_env_data, NULL, NULL, NULL,
        7, 0, K_NO_WAIT);

    /* Create time pool poll thread */
    ntp_tid = k_thread_create(&ntp_thread, ntp_stack_area, K_THREAD_STACK_SIZEOF(ntp_stack_area),
        (k_thread_entry_t)ntp_poll, NULL, NULL, NULL,
        7, 0, K_NO_WAIT);

   gc_tid = k_thread_create(&gc_thread, gc_stack_area, K_THREAD_STACK_SIZEOF(gc_stack_area),
        (k_thread_entry_t)gcloud_thread, NULL, NULL, NULL,
        7, 0, K_NO_WAIT);

    /* App thread entry */
    app_tid = k_thread_create(&app_thread, app_stack_area, K_THREAD_STACK_SIZEOF(app_stack_area),
        (k_thread_entry_t)app_gc_iot, NULL, NULL, NULL,
        7, 0, K_NO_WAIT);
}