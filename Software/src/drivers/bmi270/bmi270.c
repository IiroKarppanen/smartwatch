#define DT_DRV_COMPAT bosch_bmi270

#include <zephyr/sys/printk.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/init.h>


const struct device *bmi270;
struct sensor_value acc[3], gyr[3];
struct sensor_value full_scale, sampling_freq, oversampling;


static int init_bmi270(){

	bmi270 = DEVICE_DT_GET_ONE(bosch_bmi270);
	

	if (!device_is_ready(bmi270)) {
		printk("Device %s is not ready\n", bmi270->name);
		return 0;
	}


	/* Setting scale in G, due to loss of precision if the SI unit m/s^2
	 * is used
	 */
	full_scale.val1 = 2;            /* G */
	full_scale.val2 = 0;
	sampling_freq.val1 = 100;       /* Hz. Performance mode */
	sampling_freq.val2 = 0;
	oversampling.val1 = 1;          /* Normal mode */
	oversampling.val2 = 0;

	sensor_attr_set(bmi270, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_FULL_SCALE,
			&full_scale);
	sensor_attr_set(bmi270, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_OVERSAMPLING,
			&oversampling);
	/* Set sampling frequency last as this also sets the appropriate
	 * power mode. If already sampling, change to 0.0Hz before changing
	 * other attributes
	 */
	sensor_attr_set(bmi270, SENSOR_CHAN_ACCEL_XYZ,
			SENSOR_ATTR_SAMPLING_FREQUENCY,
			&sampling_freq);


	/* Setting scale in degrees/s to match the sensor scale */
	full_scale.val1 = 500;          /* dps */
	full_scale.val2 = 0;
	sampling_freq.val1 = 100;       /* Hz. Performance mode */
	sampling_freq.val2 = 0;
	oversampling.val1 = 1;          /* Normal mode */
	oversampling.val2 = 0;

	sensor_attr_set(bmi270, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_FULL_SCALE,
			&full_scale);
	sensor_attr_set(bmi270, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_OVERSAMPLING,
			&oversampling);
	/* Set sampling frequency last as this also sets the appropriate
	 * power mode. If already sampling, change sampling frequency to
	 * 0.0Hz before changing other attributes
	 */
	sensor_attr_set(bmi270, SENSOR_CHAN_GYRO_XYZ,
			SENSOR_ATTR_SAMPLING_FREQUENCY,
			&sampling_freq);
        
    return 0;
}


void fetch_axis(){

    sensor_sample_fetch(bmi270);

		sensor_channel_get(bmi270, SENSOR_CHAN_ACCEL_XYZ, acc);
		sensor_channel_get(bmi270, SENSOR_CHAN_GYRO_XYZ, gyr);

		printk("AX: %d.%06d; AY: %d.%06d; AZ: %d.%06d; "
		       "GX: %d.%06d; GY: %d.%06d; GZ: %d.%06d;\n",
		       acc[0].val1, acc[0].val2,
		       acc[1].val1, acc[1].val2,
		       acc[2].val1, acc[2].val2,
		       gyr[0].val1, gyr[0].val2,
		       gyr[1].val1, gyr[1].val2,
		       gyr[2].val1, gyr[2].val2);
}

/*
static const struct sensor_driver_api bmi270_driver_api = {
    .sample_fetch = fetch_axis
};
*/




SYS_INIT(init_bmi270, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY);