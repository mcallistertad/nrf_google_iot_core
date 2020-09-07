.. _mqtt_google_cloud:

nRF9160: MQTT Google Cloud
#####################
This application gathers readings from a Bosch BME680 environmental sensor and publishes to a GCP Pub/Sub topic.

Overview
********
Sensor data is saved in an array of size set in prj.conf. 
When full, the data is aggregated, a TLS session is established, we authenticate to GC IoT Core and the data is published.

Requirements
************
* Google Cloud SDK https://cloud.google.com/sdk/docs/#install_the_latest_cloud_tools_version_cloudsdk_current_version
* Python 3
* Segger J-Link debugger

Dependencies
************
* nrf-sdk v1.3 or newer - tracks master https://github.com/nrfconnect/sdk-nrf/tree/v1.3-branch
* Bosch BSEC library - https://www.bosch-sensortec.com/software-tools/software/bsec/
* nRF91 modem firmware v1.2 https://www.nordicsemi.com/-/media/Software-and-other-downloads/Dev-Kits/nRF9160-DK/nRF9160-modem-FW/mfwnrf9160120.zip
* nRF52 firmware - thingy91_nrf52_usb_uart_bridge_2019-11-29_d3130d77.hex

Getting Started
***************
In prj.conf: set gcloud variables
**CONFIG_GCLOUD_REGION="<region>"**
**CONFIG_GCLOUD_PROJECT_NAME="<project_name>"**
**CONFIG_GCLOUD_REGISTRY_NAME="<registry_name>"**
**CONFIG_GCLOUD_DEVICE_NAME="<device_name>"**

* Sign BSEC license agreement and place in nrf/ext folder
* Update BSEC path in prj.conf if BSEC version is different

* Run shell script in src/private_info to generate GC IoT Core certs/ public key
**sh create_keys.sh**

References
**********
gcloud library is based on:
https://devzone.nordicsemi.com/cfs-file/__key/telligent-evolution-components-attachments/01-27-00-00-00-00-12-59/nRF9160DKtoGoogleCloud.zip
modified for use with new ncs mqtt bindings and compatibility with Thingy91.