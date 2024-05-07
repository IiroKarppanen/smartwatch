#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>

extern struct gps_data {
    char nmea_message[100];
    char time[12];      
    char latitude[12];  
    char longitude[13];
    char status;        
};

extern struct gps_data gps_info;

void parse_nmea(const char *sentence);
void uart_cb(const struct device *x, void *user_data);
void init_gnss();
void enter_standby_mode();
void exit_standby_mode();
void exit_backup_mode();

