
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef ZEPHYR_SYSCALL_LIST_H
#define ZEPHYR_SYSCALL_LIST_H

#define K_SYSCALL_ADC_CHANNEL_SETUP 0
#define K_SYSCALL_ADC_READ 1
#define K_SYSCALL_ADC_READ_ASYNC 2
#define K_SYSCALL_ATOMIC_ADD 3
#define K_SYSCALL_ATOMIC_AND 4
#define K_SYSCALL_ATOMIC_CAS 5
#define K_SYSCALL_ATOMIC_NAND 6
#define K_SYSCALL_ATOMIC_OR 7
#define K_SYSCALL_ATOMIC_PTR_CAS 8
#define K_SYSCALL_ATOMIC_PTR_SET 9
#define K_SYSCALL_ATOMIC_SET 10
#define K_SYSCALL_ATOMIC_SUB 11
#define K_SYSCALL_ATOMIC_XOR 12
#define K_SYSCALL_CAN_ATTACH_MSGQ 13
#define K_SYSCALL_CAN_CONFIGURE 14
#define K_SYSCALL_CAN_DETACH 15
#define K_SYSCALL_CAN_GET_STATE 16
#define K_SYSCALL_CAN_RECOVER 17
#define K_SYSCALL_CAN_SEND 18
#define K_SYSCALL_CLOCK_GETTIME 19
#define K_SYSCALL_COUNTER_CANCEL_CHANNEL_ALARM 20
#define K_SYSCALL_COUNTER_GET_FREQUENCY 21
#define K_SYSCALL_COUNTER_GET_GUARD_PERIOD 22
#define K_SYSCALL_COUNTER_GET_MAX_RELATIVE_ALARM 23
#define K_SYSCALL_COUNTER_GET_MAX_TOP_VALUE 24
#define K_SYSCALL_COUNTER_GET_NUM_OF_CHANNELS 25
#define K_SYSCALL_COUNTER_GET_PENDING_INT 26
#define K_SYSCALL_COUNTER_GET_TOP_VALUE 27
#define K_SYSCALL_COUNTER_GET_VALUE 28
#define K_SYSCALL_COUNTER_IS_COUNTING_UP 29
#define K_SYSCALL_COUNTER_SET_CHANNEL_ALARM 30
#define K_SYSCALL_COUNTER_SET_GUARD_PERIOD 31
#define K_SYSCALL_COUNTER_SET_TOP_VALUE 32
#define K_SYSCALL_COUNTER_START 33
#define K_SYSCALL_COUNTER_STOP 34
#define K_SYSCALL_COUNTER_TICKS_TO_US 35
#define K_SYSCALL_COUNTER_US_TO_TICKS 36
#define K_SYSCALL_DAC_CHANNEL_SETUP 37
#define K_SYSCALL_DAC_WRITE_VALUE 38
#define K_SYSCALL_DEVICE_GET_BINDING 39
#define K_SYSCALL_DMA_START 40
#define K_SYSCALL_DMA_STOP 41
#define K_SYSCALL_EEPROM_GET_SIZE 42
#define K_SYSCALL_EEPROM_READ 43
#define K_SYSCALL_EEPROM_WRITE 44
#define K_SYSCALL_ENTROPY_GET_ENTROPY 45
#define K_SYSCALL_ESPI_CONFIG 46
#define K_SYSCALL_ESPI_FLASH_ERASE 47
#define K_SYSCALL_ESPI_GET_CHANNEL_STATUS 48
#define K_SYSCALL_ESPI_READ_FLASH 49
#define K_SYSCALL_ESPI_READ_LPC_REQUEST 50
#define K_SYSCALL_ESPI_READ_REQUEST 51
#define K_SYSCALL_ESPI_RECEIVE_OOB 52
#define K_SYSCALL_ESPI_RECEIVE_VWIRE 53
#define K_SYSCALL_ESPI_SEND_OOB 54
#define K_SYSCALL_ESPI_SEND_VWIRE 55
#define K_SYSCALL_ESPI_WRITE_FLASH 56
#define K_SYSCALL_ESPI_WRITE_LPC_REQUEST 57
#define K_SYSCALL_ESPI_WRITE_REQUEST 58
#define K_SYSCALL_FLASH_ERASE 59
#define K_SYSCALL_FLASH_GET_PAGE_COUNT 60
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_IDX 61
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_OFFS 62
#define K_SYSCALL_FLASH_GET_WRITE_BLOCK_SIZE 63
#define K_SYSCALL_FLASH_READ 64
#define K_SYSCALL_FLASH_WRITE 65
#define K_SYSCALL_FLASH_WRITE_PROTECTION_SET 66
#define K_SYSCALL_GPIO_CONFIG 67
#define K_SYSCALL_GPIO_DISABLE_CALLBACK 68
#define K_SYSCALL_GPIO_ENABLE_CALLBACK 69
#define K_SYSCALL_GPIO_GET_PENDING_INT 70
#define K_SYSCALL_GPIO_PIN_INTERRUPT_CONFIGURE 71
#define K_SYSCALL_GPIO_PORT_CLEAR_BITS_RAW 72
#define K_SYSCALL_GPIO_PORT_GET_RAW 73
#define K_SYSCALL_GPIO_PORT_SET_BITS_RAW 74
#define K_SYSCALL_GPIO_PORT_SET_MASKED_RAW 75
#define K_SYSCALL_GPIO_PORT_TOGGLE_BITS 76
#define K_SYSCALL_HWINFO_GET_DEVICE_ID 77
#define K_SYSCALL_I2C_CONFIGURE 78
#define K_SYSCALL_I2C_RECOVER_BUS 79
#define K_SYSCALL_I2C_SLAVE_DRIVER_REGISTER 80
#define K_SYSCALL_I2C_SLAVE_DRIVER_UNREGISTER 81
#define K_SYSCALL_I2C_TRANSFER 82
#define K_SYSCALL_I2S_BUF_READ 83
#define K_SYSCALL_I2S_BUF_WRITE 84
#define K_SYSCALL_I2S_CONFIGURE 85
#define K_SYSCALL_I2S_TRIGGER 86
#define K_SYSCALL_IPM_MAX_DATA_SIZE_GET 87
#define K_SYSCALL_IPM_MAX_ID_VAL_GET 88
#define K_SYSCALL_IPM_SEND 89
#define K_SYSCALL_IPM_SET_ENABLED 90
#define K_SYSCALL_KSCAN_CONFIG 91
#define K_SYSCALL_KSCAN_DISABLE_CALLBACK 92
#define K_SYSCALL_KSCAN_ENABLE_CALLBACK 93
#define K_SYSCALL_K_BUSY_WAIT 94
#define K_SYSCALL_K_CURRENT_GET 95
#define K_SYSCALL_K_FLOAT_DISABLE 96
#define K_SYSCALL_K_FUTEX_WAIT 97
#define K_SYSCALL_K_FUTEX_WAKE 98
#define K_SYSCALL_K_IS_PREEMPT_THREAD 99
#define K_SYSCALL_K_MSGQ_ALLOC_INIT 100
#define K_SYSCALL_K_MSGQ_GET 101
#define K_SYSCALL_K_MSGQ_GET_ATTRS 102
#define K_SYSCALL_K_MSGQ_NUM_FREE_GET 103
#define K_SYSCALL_K_MSGQ_NUM_USED_GET 104
#define K_SYSCALL_K_MSGQ_PEEK 105
#define K_SYSCALL_K_MSGQ_PURGE 106
#define K_SYSCALL_K_MSGQ_PUT 107
#define K_SYSCALL_K_MUTEX_INIT 108
#define K_SYSCALL_K_MUTEX_LOCK 109
#define K_SYSCALL_K_MUTEX_UNLOCK 110
#define K_SYSCALL_K_OBJECT_ACCESS_GRANT 111
#define K_SYSCALL_K_OBJECT_ALLOC 112
#define K_SYSCALL_K_OBJECT_RELEASE 113
#define K_SYSCALL_K_PIPE_ALLOC_INIT 114
#define K_SYSCALL_K_PIPE_GET 115
#define K_SYSCALL_K_PIPE_PUT 116
#define K_SYSCALL_K_PIPE_READ_AVAIL 117
#define K_SYSCALL_K_PIPE_WRITE_AVAIL 118
#define K_SYSCALL_K_POLL 119
#define K_SYSCALL_K_POLL_SIGNAL_CHECK 120
#define K_SYSCALL_K_POLL_SIGNAL_INIT 121
#define K_SYSCALL_K_POLL_SIGNAL_RAISE 122
#define K_SYSCALL_K_POLL_SIGNAL_RESET 123
#define K_SYSCALL_K_QUEUE_ALLOC_APPEND 124
#define K_SYSCALL_K_QUEUE_ALLOC_PREPEND 125
#define K_SYSCALL_K_QUEUE_CANCEL_WAIT 126
#define K_SYSCALL_K_QUEUE_GET 127
#define K_SYSCALL_K_QUEUE_INIT 128
#define K_SYSCALL_K_QUEUE_IS_EMPTY 129
#define K_SYSCALL_K_QUEUE_PEEK_HEAD 130
#define K_SYSCALL_K_QUEUE_PEEK_TAIL 131
#define K_SYSCALL_K_SEM_COUNT_GET 132
#define K_SYSCALL_K_SEM_GIVE 133
#define K_SYSCALL_K_SEM_INIT 134
#define K_SYSCALL_K_SEM_RESET 135
#define K_SYSCALL_K_SEM_TAKE 136
#define K_SYSCALL_K_SLEEP 137
#define K_SYSCALL_K_STACK_ALLOC_INIT 138
#define K_SYSCALL_K_STACK_POP 139
#define K_SYSCALL_K_STACK_PUSH 140
#define K_SYSCALL_K_STR_OUT 141
#define K_SYSCALL_K_THREAD_ABORT 142
#define K_SYSCALL_K_THREAD_CREATE 143
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_GET 144
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_SET 145
#define K_SYSCALL_K_THREAD_DEADLINE_SET 146
#define K_SYSCALL_K_THREAD_JOIN 147
#define K_SYSCALL_K_THREAD_NAME_COPY 148
#define K_SYSCALL_K_THREAD_NAME_SET 149
#define K_SYSCALL_K_THREAD_PRIORITY_GET 150
#define K_SYSCALL_K_THREAD_PRIORITY_SET 151
#define K_SYSCALL_K_THREAD_RESUME 152
#define K_SYSCALL_K_THREAD_STACK_SPACE_GET 153
#define K_SYSCALL_K_THREAD_START 154
#define K_SYSCALL_K_THREAD_SUSPEND 155
#define K_SYSCALL_K_THREAD_TIMEOUT_EXPIRES_TICKS 156
#define K_SYSCALL_K_THREAD_TIMEOUT_REMAINING_TICKS 157
#define K_SYSCALL_K_TIMER_EXPIRES_TICKS 158
#define K_SYSCALL_K_TIMER_REMAINING_TICKS 159
#define K_SYSCALL_K_TIMER_START 160
#define K_SYSCALL_K_TIMER_STATUS_GET 161
#define K_SYSCALL_K_TIMER_STATUS_SYNC 162
#define K_SYSCALL_K_TIMER_STOP 163
#define K_SYSCALL_K_TIMER_USER_DATA_GET 164
#define K_SYSCALL_K_TIMER_USER_DATA_SET 165
#define K_SYSCALL_K_UPTIME_TICKS 166
#define K_SYSCALL_K_USLEEP 167
#define K_SYSCALL_K_WAKEUP 168
#define K_SYSCALL_K_YIELD 169
#define K_SYSCALL_LED_BLINK 170
#define K_SYSCALL_LED_OFF 171
#define K_SYSCALL_LED_ON 172
#define K_SYSCALL_LED_SET_BRIGHTNESS 173
#define K_SYSCALL_LOG_BUFFERED_CNT 174
#define K_SYSCALL_LOG_FILTER_SET 175
#define K_SYSCALL_LOG_PANIC 176
#define K_SYSCALL_LOG_PROCESS 177
#define K_SYSCALL_MAXIM_DS3231_GET_SYNCPOINT 178
#define K_SYSCALL_MAXIM_DS3231_REQ_SYNCPOINT 179
#define K_SYSCALL_NET_ADDR_NTOP 180
#define K_SYSCALL_NET_ADDR_PTON 181
#define K_SYSCALL_NET_ETH_GET_PTP_CLOCK_BY_INDEX 182
#define K_SYSCALL_NET_IF_IPV4_ADDR_ADD_BY_INDEX 183
#define K_SYSCALL_NET_IF_IPV4_ADDR_LOOKUP_BY_INDEX 184
#define K_SYSCALL_NET_IF_IPV4_ADDR_RM_BY_INDEX 185
#define K_SYSCALL_NET_IF_IPV4_SET_GW_BY_INDEX 186
#define K_SYSCALL_NET_IF_IPV4_SET_NETMASK_BY_INDEX 187
#define K_SYSCALL_NET_IF_IPV6_ADDR_ADD_BY_INDEX 188
#define K_SYSCALL_NET_IF_IPV6_ADDR_LOOKUP_BY_INDEX 189
#define K_SYSCALL_NET_IF_IPV6_ADDR_RM_BY_INDEX 190
#define K_SYSCALL_PECI_CONFIG 191
#define K_SYSCALL_PECI_DISABLE 192
#define K_SYSCALL_PECI_ENABLE 193
#define K_SYSCALL_PECI_TRANSFER 194
#define K_SYSCALL_PS2_CONFIG 195
#define K_SYSCALL_PS2_DISABLE_CALLBACK 196
#define K_SYSCALL_PS2_ENABLE_CALLBACK 197
#define K_SYSCALL_PS2_READ 198
#define K_SYSCALL_PS2_WRITE 199
#define K_SYSCALL_PTP_CLOCK_GET 200
#define K_SYSCALL_PWM_GET_CYCLES_PER_SEC 201
#define K_SYSCALL_PWM_PIN_SET_CYCLES 202
#define K_SYSCALL_SENSOR_ATTR_SET 203
#define K_SYSCALL_SENSOR_CHANNEL_GET 204
#define K_SYSCALL_SENSOR_SAMPLE_FETCH 205
#define K_SYSCALL_SENSOR_SAMPLE_FETCH_CHAN 206
#define K_SYSCALL_SPI_RELEASE 207
#define K_SYSCALL_SPI_TRANSCEIVE 208
#define K_SYSCALL_UART_CONFIGURE 209
#define K_SYSCALL_UART_CONFIG_GET 210
#define K_SYSCALL_UART_DRV_CMD 211
#define K_SYSCALL_UART_ERR_CHECK 212
#define K_SYSCALL_UART_IRQ_ERR_DISABLE 213
#define K_SYSCALL_UART_IRQ_ERR_ENABLE 214
#define K_SYSCALL_UART_IRQ_IS_PENDING 215
#define K_SYSCALL_UART_IRQ_RX_DISABLE 216
#define K_SYSCALL_UART_IRQ_RX_ENABLE 217
#define K_SYSCALL_UART_IRQ_TX_DISABLE 218
#define K_SYSCALL_UART_IRQ_TX_ENABLE 219
#define K_SYSCALL_UART_IRQ_UPDATE 220
#define K_SYSCALL_UART_LINE_CTRL_GET 221
#define K_SYSCALL_UART_LINE_CTRL_SET 222
#define K_SYSCALL_UART_MUX_FIND 223
#define K_SYSCALL_UART_POLL_IN 224
#define K_SYSCALL_UART_POLL_OUT 225
#define K_SYSCALL_UART_RX_DISABLE 226
#define K_SYSCALL_UART_RX_ENABLE 227
#define K_SYSCALL_UART_TX 228
#define K_SYSCALL_UART_TX_ABORT 229
#define K_SYSCALL_WDT_DISABLE 230
#define K_SYSCALL_WDT_FEED 231
#define K_SYSCALL_WDT_SETUP 232
#define K_SYSCALL_ZEPHYR_FPUTC 233
#define K_SYSCALL_ZEPHYR_FWRITE 234
#define K_SYSCALL_ZSOCK_ACCEPT 235
#define K_SYSCALL_ZSOCK_BIND 236
#define K_SYSCALL_ZSOCK_CLOSE 237
#define K_SYSCALL_ZSOCK_CONNECT 238
#define K_SYSCALL_ZSOCK_FCNTL 239
#define K_SYSCALL_ZSOCK_GETHOSTNAME 240
#define K_SYSCALL_ZSOCK_GETSOCKNAME 241
#define K_SYSCALL_ZSOCK_GETSOCKOPT 242
#define K_SYSCALL_ZSOCK_INET_PTON 243
#define K_SYSCALL_ZSOCK_LISTEN 244
#define K_SYSCALL_ZSOCK_POLL 245
#define K_SYSCALL_ZSOCK_RECVFROM 246
#define K_SYSCALL_ZSOCK_SENDMSG 247
#define K_SYSCALL_ZSOCK_SENDTO 248
#define K_SYSCALL_ZSOCK_SETSOCKOPT 249
#define K_SYSCALL_ZSOCK_SHUTDOWN 250
#define K_SYSCALL_ZSOCK_SOCKET 251
#define K_SYSCALL_ZSOCK_SOCKETPAIR 252
#define K_SYSCALL_Z_CLOCK_HW_CYCLES_PER_SEC_RUNTIME_GET 253
#define K_SYSCALL_Z_ERRNO 254
#define K_SYSCALL_Z_LOG_HEXDUMP_FROM_USER 255
#define K_SYSCALL_Z_LOG_STRING_FROM_USER 256
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_LOCK 257
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_UNLOCK 258
#define K_SYSCALL_Z_ZEPHYR_READ_STDIN 259
#define K_SYSCALL_Z_ZEPHYR_WRITE_STDOUT 260
#define K_SYSCALL_Z_ZSOCK_GETADDRINFO_INTERNAL 261
#define K_SYSCALL_BAD 262
#define K_SYSCALL_LIMIT 263


#ifndef _ASMLANGUAGE

#include <stdint.h>

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_SYSCALL_LIST_H */