#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <SEGGER_RTT.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/uart.h>
#include <lvgl.h>
#include <ui.h>


#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);




#define LVGL_THREAD_STACK_SIZE 15360
#define LVGL_THREAD_PRIORITY 1

// LVGL thread
K_THREAD_STACK_DEFINE(lvgl_thread_stack, LVGL_THREAD_STACK_SIZE);
struct k_thread lvgl_thread_data;

// LVGL task
void lvgl_task(void *p1, void *p2, void *p3)
{
    while (1) {
        lv_task_handler();
        k_msleep(50);  
    }
}



#define UART_BUF_SIZE 1024

static uint8_t uart_buf[UART_BUF_SIZE];

static size_t buf_idx = 0;


struct gps_data {
    char time[12];      // UTC time in HHMMSS.SSS format
    char latitude[12];  // Latitude in DDMM.MMMM format
    char longitude[13]; // Longitude in DDDMM.MMMM format
    char status;        // Status of GPS fix (A = valid, V = invalid)
};



static struct gps_data gps_info;


static void parse_nmea(const char *sentence) {
    printk("Received NMEA sentence: %s\n", sentence);

	// $GPGLL,,,,,174518.086,V,N*7A

	//printk("len: %d", strlen(sentence));

	//  ,,,,174518.086,V,

	int prefix;
	int suffix;

	size_t len = strlen(sentence);

	if (strstr(sentence, "GPGLL") != NULL) {
		
		prefix = 7;
		suffix = 17;

		// Calculate the start and length of the substring to extract
		char* start_ptr = sentence + prefix; // Pointer to the start of the substring
		size_t substring_len = len - prefix - suffix; // Length of the substring

		// Allocate memory for the substring (including space for the null terminator)
		char pos[substring_len + 1];

		// Copy the substring from the original sentence
		memcpy(pos, start_ptr, substring_len);
		pos[substring_len] = '\0'; // Null terminate the pos substring

		// Print the pos substring
		printk("Position: %s\n", pos);

		if(strcmp(pos, ",,,,\n") == 0){
			lv_label_set_text(ui_posLabel, pos);
		}
		else{
			lv_label_set_text(ui_posLabel, "No Fix");
		}

		prefix = 11;
		suffix = 11;

		// Calculate the start and length of the substring to extract
		start_ptr = sentence + prefix; // Pointer to the start of the substring
		substring_len = len - prefix - suffix; // Length of the substring

		// Allocate memory for the substring (including space for the null terminator)
		char time[substring_len + 1];

		// Copy the substring from the original sentence
		memcpy(time, start_ptr, substring_len);
		time[substring_len] = '\0'; // Null terminate the time substring

		// Create a new string to hold the formatted time (including null terminator)
		char formatted_time[9]; // "HH:MM:SS\0"

		// Insert colons at specific positions to format the time string
		sprintf(formatted_time, "%c%c:%c%c:%c%c", 
				time[0], time[1], // Hours
				time[2], time[3], // Minutes
				time[4], time[5]); // Seconds

		// Print the formatted time string
		printk("Formatted Time: %s\n", formatted_time);
		lv_label_set_text(ui_utcLabel, formatted_time);


		lv_label_set_text(ui_statusLabel, sentence);

	}
}


static void uart_cb(const struct device *x, void *user_data) {
    uart_irq_update(x);
    int data_length = 0;

    if (uart_irq_rx_ready(x)) {
        data_length = uart_fifo_read(x, &uart_buf[buf_idx], UART_BUF_SIZE - buf_idx);
        buf_idx += data_length;

        // Search for end of line characters and process sentences
        for (size_t i = 0; i < buf_idx; i++) {
            if (uart_buf[i] == '\n' || uart_buf[i] == '\r') {
                uart_buf[i] = 0; // Null-terminate the sentence
                parse_nmea((char *)uart_buf);
                buf_idx = 0; // Reset buffer index after processing
                break;
            }
        }
    }
}



void main(void){
	

	SEGGER_RTT_Init();
	printk("RTT LOG\n\n");
    k_sleep(K_SECONDS(3));



	const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	if (!device_is_ready(display_dev))
	{
		printk("Display not ready\n");
		return;
	}

	// Initialize LVGL
    lv_init();
	ui_init();

    k_thread_create(&lvgl_thread_data, lvgl_thread_stack,
        K_THREAD_STACK_SIZEOF(lvgl_thread_stack),
        lvgl_task, NULL, NULL, NULL,
        LVGL_THREAD_PRIORITY, 0, K_NO_WAIT);




	const struct device *uart;
	uart = device_get_binding("UART_0");
	
    const struct uart_config uart_cfg = {
        .baudrate = 9600,
        .parity = UART_CFG_PARITY_NONE,
        .stop_bits = UART_CFG_STOP_BITS_1,
        .data_bits = UART_CFG_DATA_BITS_8,
        .flow_ctrl = UART_CFG_FLOW_CTRL_NONE
    };

	int ret;
    ret = uart_irq_callback_user_data_set(uart, uart_cb, NULL);
	if(ret != 0){
		printk("UART Callback configure failed with error code: %d", ret);
	}

	uart_irq_rx_enable(uart);
	printk("UART loopback start!\n");


	while (1) {
	
		
		printk("-\n");
		k_sleep(K_MSEC(1000));
	}
    
}

