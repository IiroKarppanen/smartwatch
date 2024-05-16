#include <zephyr/kernel.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/fuel_gauge.h>

struct BatteryData {
    int8_t status;
    int runtime_to_empty;  
    int runtime_to_full;   
    int relative_state_of_charge;  
    int voltage; 
    int current_draw;
};

extern struct BatteryData battery_data;

void fetch_battery_data(void);
void init_gauge();