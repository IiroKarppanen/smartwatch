#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel/thread_stack.h>
#include "inertial_measurement.h"


#define MEASUREMENT_THREAD_STACK_SIZE 4096
#define MEASUREMENT_THREAD_PRIORITY 5

K_THREAD_STACK_DEFINE(measurement_thread_stack, MEASUREMENT_THREAD_STACK_SIZE);
struct k_thread measurement_thread_data;

const struct device *bmi270;
struct sensor_value acc[3], gyr[3];
struct sensor_value full_scale, sampling_freq, oversampling;


void measurement_task(){
    while (1) {
        sensor_sample_fetch(bmi270);

		sensor_channel_get(bmi270, SENSOR_CHAN_ACCEL_XYZ, acc);
		sensor_channel_get(bmi270, SENSOR_CHAN_GYRO_XYZ, gyr);

        k_msleep(50);  
		
    }
}


void init_bmi270(){

	bmi270 = DEVICE_DT_GET_ONE(bosch_bmi270);
	
	if (!device_is_ready(bmi270)) {
		printk("Device %s is not ready\n", bmi270->name);
		return 0;
	}

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



    k_thread_create(&measurement_thread_data, measurement_thread_stack,
        K_THREAD_STACK_SIZEOF(measurement_thread_stack),
        measurement_task, NULL, NULL, NULL,
        MEASUREMENT_THREAD_PRIORITY, 0, K_NO_WAIT);

}



SYS_INIT(init_bmi270, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);