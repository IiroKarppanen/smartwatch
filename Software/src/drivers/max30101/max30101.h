#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <ui.h>

extern double bpm;

void init_max30101(void);
void fetch_pulse(void);

