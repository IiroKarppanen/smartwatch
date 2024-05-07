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

const struct device *dev;

struct BatteryData {
    int runtime_to_empty;  
    int runtime_to_full;   
    int relative_state_of_charge;  
    int voltage; 
};

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
    }
};

struct BatteryData fetch_battery_data(void) {
    struct BatteryData battery_data;

    int ret = fuel_gauge_get_prop(dev, props, ARRAY_SIZE(props));
    if (ret == 0) {
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
    } else {
        printk("ERROR: Unable to fetch battery data\n");
    }

    return battery_data;
}


void init_gauge(){

    dev = DEVICE_DT_GET_ANY(maxim_max17048);
	int ret = 0;

	if (dev == NULL) {
		printk("ERROR: Unable to find max17048 sensor.\n");
		return 0;
	}

}


SYS_INIT(init_gauge, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);