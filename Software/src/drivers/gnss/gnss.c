#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/ring_buffer.h>
#include <lvgl.h>
#include <ui.h>


#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

const struct gpio_dt_spec extint = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, extint_gpios);
const struct gpio_dt_spec forceon = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, forceon_gpios);


const struct uart_config uart_cfg = {
	.baudrate = 9600,
	.parity = UART_CFG_PARITY_NONE,
	.stop_bits = UART_CFG_STOP_BITS_1,
	.data_bits = UART_CFG_DATA_BITS_8,
	.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
};


struct gps_data {
	char nmea_message[100];
    char time[12];      
    char latitude[12];  
    char longitude[13];
    char status;        
};

struct gps_data gps_info;

const struct device *uart;

#define RX_BUF_SIZE 80
static uint8_t rx_buf[RX_BUF_SIZE] = {0}; 
static size_t rx_buf_idx = 0;



static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
    switch (evt->type) {
        case UART_RX_RDY:

			// Append the received character to the buffer
			rx_buf[rx_buf_idx++] = evt->data.rx.buf[0];

			// Check for end of message conditions
			if (rx_buf_idx >= (RX_BUF_SIZE - 1)) {  
				rx_buf[rx_buf_idx] = '\0';  // Null-terminate the buffer

				int start_index = -1;
				int end_index = -1;

				// Find the start ('$') and end ('\n' or '\r') of NMEA message
				for (int i = 0; i < strlen(rx_buf); i++) {
					if (rx_buf[i] == '$') {
						start_index = i;
					}
					if (rx_buf[i] == '\n' || rx_buf[i] == '\r') {
						end_index = i;
						break; 
					}
				}

				if (start_index != -1 && end_index != -1) {
					int length = end_index - start_index;
					strncpy(gps_info.nmea_message, &rx_buf[start_index], length);
					gps_info.nmea_message[length] = '\0'; 
					printk("Extracted NMEA Message: %s\n", gps_info.nmea_message);
				} else {
					printk("NMEA Message not found or invalid format\n");
				}


				/* PARSING PROCESS */

				char time[15] = "";
				char latitude[25] = "";
				char longitude[25] = "";
				char status[2] = "";

				if(strstr(gps_info.nmea_message, "GPRMC") != NULL){


					printk("Extracting values from: %s\n", gps_info.nmea_message);

					// Create a copy of the input string for tokenization
					char copy[strlen(gps_info.nmea_message) + 1];
					strcpy(copy, gps_info.nmea_message);

					char *token;
					token = strtok(copy, ",");

				
					// Tokenize the string using ',' as delimiter and parse relevant fields
					int field_count = 1;
					while ((token = strtok(NULL, ",")) != NULL) {
						switch (field_count) {
							case 1: // Skip sentence identifier ($GPRMC or $GPGLL)
								break;
							case 2: // Time (HHMMSS.SSS format)
								if (strlen(token) >= 6) {
									strncpy(time, token, sizeof(time) - 1);
									time[sizeof(time) - 1] = '\0'; // Ensure null-termination
								}
								break;
							case 3: // GPS Fix Status (A or V)
								if (strlen(token) > 0) {
									strncpy(status, token, sizeof(status) - 1);
									status[sizeof(status) - 1] = '\0'; // Ensure null-termination
								}
								break;
							case 4: // Latitude (DDMM.MMMM format or empty)
								if (strlen(token) > 0) {
									strncpy(latitude, token, sizeof(latitude) - 1);
									latitude[sizeof(latitude) - 1] = '\0'; // Ensure null-termination
								}
								break;
							case 5: // Latitude direction (N or S)
								if (strlen(latitude) > 0) {
									strncat(latitude, token, sizeof(latitude) - strlen(latitude) - 1);
									latitude[sizeof(latitude) - 1] = '\0'; // Ensure null-termination
								}
								break;
							case 6: // Longitude (DDDMM.MMMM format or empty)
								if (strlen(token) > 0) {
									strncpy(longitude, token, sizeof(longitude) - 1);
									longitude[sizeof(longitude) - 1] = '\0'; // Ensure null-termination
								}
								break;
							case 7: // Longitude direction (E or W)
								if (strlen(longitude) > 0) {
									strncat(longitude, token, sizeof(longitude) - strlen(longitude) - 1);
									longitude[sizeof(longitude) - 1] = '\0'; // Ensure null-termination
								}
								break;
							default:
								break;
						}
						field_count++;
					}

					if (strlen(time) > 0) {
						printk("time: %s\n", time);
					}
					if (strlen(latitude) > 0) {
						printk("latitude: %s\n", latitude);
					}
					if (strlen(longitude) > 0) {
						printk("longitude: %s\n", longitude);
					}
					if (strlen(status) > 0) {
						printk("status: %s\n", status);
					}

				}
				

				// Reset buffer for the next message
				rx_buf_idx = 0;
				memset(rx_buf, 0, sizeof(rx_buf));
			}

            break;

        case UART_RX_BUF_REQUEST:
            uart_rx_buf_rsp(dev, rx_buf, sizeof(rx_buf));
            break;


        case UART_RX_DISABLED:

            int ret = uart_rx_enable(dev, rx_buf, sizeof(rx_buf), 100);
            if (ret != 0) {
                printk("uart rx enable error %d\n", ret);
            }
            break;

        default:
            break;
    }
}


void init_gnss(){

	gpio_pin_configure_dt(&extint, GPIO_OUTPUT_HIGH);

	//uart = device_get_binding("UART_0");
	uart = DEVICE_DT_GET(DT_NODELABEL(uart0));
	if (!uart) {
        printk("UART device not found\n");
        return;
    }
	
	int ret;
	ret = uart_configure(uart, &uart_cfg); 
	if(ret != 0){
		printk("UART Configure ERROR %d", ret);
	}

	ret = uart_callback_set(uart, uart_cb, NULL);
	if(ret != 0){
		printk("UART CALLBACK CONFIGURE ERROR %d\n", ret);
	}
	
	ret = uart_rx_enable(uart, rx_buf, sizeof(rx_buf), 100);
	if(ret != 0){
		printk("uart rx enable error %d\n", ret);
	}

	printk("UART CONFIGURE COMPLETE!\n");
	

	k_msleep(3000); 
	printk("Entering standby mode...\n");
	enter_standby_mode();

	//exit_standby_mode();

}






void enable_periodic_standby_mode() {
    const char *command = "$PMTK225,2,3000,12000,18000,72000*15\r\n";
	// 3 seconds full mode
	// 12 seconds sleep
	// 72 seconds standby

    uart_tx(uart, (uint8_t)command, sizeof((uint8_t)command), SYS_FOREVER_MS);
}


void enter_standby_mode(){

	uart_rx_disable(uart); // Disable RX before sending standby command

	gpio_pin_set_dt(&extint, 0);
	const char cmd[] = "$PMTK161,0*28\r\n";
	int ret = uart_tx(uart, (const uint8_t *)cmd, strlen(cmd), SYS_FOREVER_MS);
	if(ret != 0){
		printk("UART TX ERROR %d\n", ret);
	}

	uart_rx_enable(uart, rx_buf, sizeof(rx_buf), 100);

}

void exit_standby_mode(){
    gpio_pin_set_dt(&extint, 1);
}


void exit_backup_mode(){
    gpio_pin_set_dt(&forceon, 1);
    k_sleep(K_MSEC(1000));
    gpio_pin_set_dt(&forceon, 0);
}


SYS_INIT(init_gnss, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);