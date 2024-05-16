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

#define BATTERY_CAPACITY 720000 // In Seconds

const struct device *gauge;

struct BatteryData {
    int8_t status;
    int runtime_to_empty;  
    int runtime_to_full;   
    int relative_state_of_charge;  
    int voltage; 
    int current_draw;
    int current;
    int remaining;
};

struct BatteryData battery_data;

struct fuel_gauge_get_property props[] = {
    {
        .property_type = FUEL_GAUGE_RUNTIME_TO_EMPTY,
    },
    {
        .property_type = FUEL_GAUGE_RUNTIME_TO_FULL,
    },
    {
        .property_type = FUEL_GAUGE_RELATIVE_STATE_OF_CHARGE,
    },
    {
        .property_type = FUEL_GAUGE_VOLTAGE,
    },
};
 
void fetch_battery_data(void) {

    int ret = fuel_gauge_get_prop(gauge, props, ARRAY_SIZE(props));
    if (ret == 0) {
        battery_data.status = 0;

        if (props[0].status == 0) {
            battery_data.runtime_to_empty = props[0].value.runtime_to_empty;
        }
        if (props[1].status == 0) {
            battery_data.runtime_to_full = props[1].value.runtime_to_full;
        }
        if (props[2].status == 0) {
            battery_data.relative_state_of_charge = props[2].value.relative_state_of_charge;
        }
        if (props[3].status == 0) {
            battery_data.voltage = props[3].value.voltage;
        }


        if(battery_data.runtime_to_empty != 0 && battery_data.relative_state_of_charge != 0){
            uint16_t seconds_left = battery_data.runtime_to_empty * 60;
            uint16_t capacity_in_seconds = battery_data.relative_state_of_charge * (BATTERY_CAPACITY / 100);
            battery_data.current_draw = capacity_in_seconds / seconds_left;
        }
        
    } 
    else {
        printk("ERROR: Unable to fetch battery data. Code: %d\n", ret);
        battery_data.status = -1;
    }

}


void init_gauge(){

    gauge = DEVICE_DT_GET_ANY(maxim_max17048);
	if (gauge == NULL) {
		printk("ERROR: Unable to find max17048 sensor.\n");
	}

}


SYS_INIT(init_gauge, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY);