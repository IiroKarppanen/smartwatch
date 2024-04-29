#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <ui.h>

const struct device *uart;


#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

const struct gpio_dt_spec extint = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, extint_gpios);
const struct gpio_dt_spec forceon = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, forceon_gpios);



#define UART_BUF_SIZE 1024

static uint8_t uart_buf[UART_BUF_SIZE];

static size_t buf_idx = 0;


struct gps_data {
    char time[12];      
    char latitude[12];  
    char longitude[13];
    char status;        
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

    
	if (strstr(sentence, "GPGGA") != NULL) {


		//lv_label_set_text(ui_posLabel, sentence);

		/*¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨
		
		
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

		*/
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



void init_gnss(){

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

	k_msleep(5000); 
	uart_irq_rx_enable(uart);

    gpio_pin_configure_dt(&extint, GPIO_OUTPUT_LOW);
	//gpio_pin_configure_dt(&forceon, GPIO_OUTPUT_HIGH);
	
	enter_standby_mode();
	//exit_standby_mode();

}

const char *standby_command = "$PMTK161,0*28";


void send_uart_command(const struct device *uart, const char *cmd) {
    size_t cmd_len = strlen(cmd);
    uart_tx(uart, (const uint8_t *)cmd, cmd_len, SYS_FOREVER_MS);
}


void enter_standby_mode(){
    // or send “$PMTK161,0*28” via uart
    //gpio_pin_set_dt(&extint, 0);
	send_uart_command(uart, standby_command);
}

void exit_standby_mode(){
    // or send anything via uart
    gpio_pin_set_dt(&extint, 1);
}

void exit_backup_mode(){
    gpio_pin_set_dt(&forceon, 1);
    k_sleep(K_MSEC(1000));
    gpio_pin_set_dt(&forceon, 0);
}


SYS_INIT(init_gnss, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);