#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel/thread_stack.h>

extern struct sensor_value acc[3], gyr[3];

void measurement_task();
void init_bmi270();