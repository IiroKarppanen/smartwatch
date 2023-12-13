#include <sys/printk.h>
#include <drivers/sensor.h>
#include "accelometer.h"

int err;

const struct device *accelometer = DEVICE_DT_GET_ANY(st_lis2dh);

void fetch_accelometer_data()
{
	static unsigned int count;
	struct sensor_value accel[3];
	struct sensor_value temperature;
	const char *overrun = "";
	int rc = sensor_sample_fetch(accelometer);

	++count;
	if (rc == -EBADMSG) {
		/* Sample overrun.  Ignore in polled mode. */
		if (IS_ENABLED(CONFIG_LIS2DH_TRIGGER)) {
			overrun = "[OVERRUN] ";
		}
		rc = 0;
	}
	if (rc == 0) {
		rc = sensor_channel_get(accelometer,
					SENSOR_CHAN_ACCEL_XYZ,
					accel);
	}
	if (rc < 0) {
		printk("ERROR: Update failed: %d\n", rc);
	} else {
		printk("#%u @ %u ms: %sx %f , y %f , z %f",
		       count, k_uptime_get_32(), overrun,
		       sensor_value_to_double(&accel[0]),
		       sensor_value_to_double(&accel[1]),
		       sensor_value_to_double(&accel[2]));
	}

	if (IS_ENABLED(CONFIG_LIS2DH_MEASURE_TEMPERATURE)) {
		if (rc == 0) {
			rc = sensor_channel_get(accelometer, SENSOR_CHAN_DIE_TEMP, &temperature);
			if (rc < 0) {
				printk("\nERROR: Unable to read temperature:%d\n", rc);
			} else {
				printk(", t %f\n", sensor_value_to_double(&temperature));
			}
		}

	} else {
		printk("\n");
	}
}