#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>


#include <stdio.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <SEGGER_RTT.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/pwm.h>
//#include <zephyr/drivers/dma.h>
//#include "drivers/gc9a01/gc9a01.h"

#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <zephyr/drivers/pwm.h>
#include <ui.h>

#include "battery_icon.c"


//#include <time.h>
//#include "drivers/lis2mdl/lis2mdl.h"
//#include "drivers/rtc/rtc.h"

//#define LED0_NODE DT_ALIAS(led0)
//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

#define LV_USE_ANIMATION    1

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

const struct device *display_dev;

#define MAX_FPS_BUFFER_LEN 10

void update_fps(lv_obj_t *fps_label, uint32_t fps) {
    static char fps_str[MAX_FPS_BUFFER_LEN];
    snprintf(fps_str, MAX_FPS_BUFFER_LEN, "FPS: %u", fps);
    lv_label_set_text(fps_label, fps_str);
}


// Function to create a random value within a range
static int32_t get_random(int32_t min, int32_t max) {
    return min + rand() % (max - min + 1);
}

void animate_x(lv_obj_t *obj, int32_t start, int32_t end, uint16_t duration, uint16_t delay, uint16_t repeat) {
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_values(&a, start, end);
    lv_anim_set_time(&a, duration);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_repeat_count(&a, repeat);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);  // Use an ease-in-out path
    lv_anim_start(&a);
}

void animate_y(lv_obj_t *obj, int32_t start, int32_t end, uint16_t duration, uint16_t delay, uint16_t repeat) {
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);  // Use lv_obj_set_y for y-axis animation
    lv_anim_set_values(&a, start, end);
    lv_anim_set_time(&a, duration);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_repeat_count(&a, repeat);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);  // Use an ease-in-out path
    lv_anim_start(&a);
}

void main(void){

	SEGGER_RTT_Init();
	printk("RTT LOG\n\n");
    k_sleep(K_SECONDS(3));

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    //display_dev = DEVICE_DT_GET_ANY(gc9a01);
	printk("start project display\r\n");
	if (!device_is_ready(display_dev))
	{
		LOG_ERR("Device not ready, aborting test");
		return;
	}

	// Initialize LVGL
    lv_init();

	// Create a screen
    lv_obj_t *screen = lv_scr_act();

	static lv_style_t bg_style;
	lv_style_init(&bg_style);
	lv_style_set_bg_color(&bg_style, lv_color_make(0, 0, 0)); 
    lv_obj_add_style(screen, &bg_style, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Create an image object
    lv_obj_t *image = lv_img_create(screen);

    // Set the image source to the C array
    lv_img_set_src(image, &battery_icon);

	// Create a label to display FPS
    lv_obj_t *fps_label = lv_label_create(screen);
    lv_label_set_text(fps_label, "FPS: 0");
    lv_obj_align(fps_label, NULL, 0, 110);

    // Create a style for the label
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_color_make(230, 230, 230)); 
    lv_style_set_text_font(&style, &lv_font_montserrat_32);
    lv_obj_add_style(fps_label, &style, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_color_t bg_color = LV_COLOR_MAKE(0, 0, 0);  // Black color

	// Start the FPS label animation
	animate_x(fps_label, 0, 239, 7000, 5, LV_ANIM_REPEAT_INFINITE);
    animate_y(fps_label, 0, 239, 5000, 0, LV_ANIM_REPEAT_INFINITE);

    // Variables for FPS calculation
    uint32_t fps = 0;
    uint32_t frame_count = 0;
    uint32_t last_tick = k_uptime_get();

	/*
    // Create a style for the label
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_make(1, 1, 1));  // Set background color to black
    lv_style_set_text_color(&style, lv_color_make(116, 77, 140));  // Set text color to white
    lv_style_set_text_font(&style, &lv_font_montserrat_32); 

    // Create a label with the specified style
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello World!");
    lv_obj_add_style(label, &style, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Set the position of the label (optional)
    lv_obj_align(label, NULL, 30, 120);
	*/
    
    /* 
	s[0] = 1;
	s[1] = 1;
	uint32_t bytes=240*240*2;
	uint32_t count=bytes/sizeof(uint64_t);
	uint64_t *buf=malloc(bytes);
    */

    printk("LVGL INIT\n\n");
    //k_msleep(500);




	while (1) {

        // Simulate some processing
        k_msleep(1);  // Adjust this delay based on your application's workload

        // Calculate FPS
        frame_count++;
        uint32_t current_tick = k_uptime_get();
        if (current_tick - last_tick >= 1000) {
            fps = frame_count;
            frame_count = 0;
            last_tick = current_tick;

            // Update the FPS label
            update_fps(fps_label, fps);
        }

        // LVGL task handler
        lv_task_handler();

        /*

		for(int i = 0; i<count; ++i)
		{
			buf[i]=next();
		}
	
		gc9a01_write(display, 1, 1, NULL, buf);
        */

    }
}




/*
// Framebuffer
uint64_t buf;

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

static uint64_t s[2];

uint64_t next(void) {
	const uint64_t s0 = s[0];
	uint64_t s1 = s[1];
	const uint64_t result = rotl(s0 + s1, 17) + s0;

	s1 ^= s0;
	s[0] = rotl(s0, 49) ^ s1 ^ (s1 << 21); // a, b
	s[1] = rotl(s1, 28); // c

	return result;
}
*/