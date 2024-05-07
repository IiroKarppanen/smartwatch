#include "ui.h"
#include "../sensor_data/inertial_measurement.h"

char ax_str[10]; 
char ay_str[10]; 
char az_str[10]; 
char gx_str[10]; 
char gy_str[10]; 
char gz_str[10]; 

void update_labels(){

    snprintf(ax_str, sizeof(ax_str), "AX %d", acc[0].val1);
    snprintf(ay_str, sizeof(ay_str), "AY %d", acc[1].val1);
    snprintf(az_str, sizeof(az_str), "AZ %d", acc[2].val1);
    snprintf(gx_str, sizeof(gx_str), "GX %d", gyr[0].val1);
    snprintf(gy_str, sizeof(gy_str), "GY %d", gyr[1].val1);
    snprintf(gz_str, sizeof(gz_str), "GZ %d", gyr[2].val1);

    lv_label_set_text(ui_AXLabel, ax_str);
    lv_label_set_text(ui_AYLabel, ay_str);
    lv_label_set_text(ui_AZLabel, az_str);
    lv_label_set_text(ui_GXLabel, gx_str);
    lv_label_set_text(ui_GYLabel, gy_str);
    lv_label_set_text(ui_GZLabel, gz_str);
    
}

void ui_SensorTest_screen_init(void)
{
    ui_SensorTest = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SensorTest, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_set_style_bg_color(ui_SensorTest, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SensorTest, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label12 = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label12, 0);
    lv_obj_set_y(ui_Label12, -86);
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "Accelometer");
    lv_obj_set_style_text_font(ui_Label12, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Label12, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Label12, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Label12, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Label12, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Label12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Label12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Label12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Label12, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_AYLabel = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_AYLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_AYLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_AYLabel, -25);
    lv_obj_set_y(ui_AYLabel, -32);
    lv_obj_set_align(ui_AYLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_AYLabel, "Y - ");

    ui_AZLabel = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_AZLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_AZLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_AZLabel, -25);
    lv_obj_set_y(ui_AZLabel, -11);
    lv_obj_set_align(ui_AZLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_AZLabel, "Z - ");

    ui_Label16 = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label16, 0);
    lv_obj_set_y(ui_Label16, 18);
    lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label16, "Gyroscope");
    lv_obj_set_style_text_font(ui_Label16, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Label16, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Label16, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Label16, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Label16, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Label16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Label16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Label16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Label16, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_GYLabel = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_GYLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_GYLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GYLabel, -25);
    lv_obj_set_y(ui_GYLabel, 72);
    lv_obj_set_align(ui_GYLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_GYLabel, "Y - ");

    ui_GZLabel = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_GZLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_GZLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GZLabel, -25);
    lv_obj_set_y(ui_GZLabel, 95);
    lv_obj_set_align(ui_GZLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_GZLabel, "Z - ");

    ui_GXLabel = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_GXLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_GXLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GXLabel, -25);
    lv_obj_set_y(ui_GXLabel, 48);
    lv_obj_set_align(ui_GXLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_GXLabel, "X - ");

    ui_AXLabel = lv_label_create(ui_SensorTest);
    lv_obj_set_width(ui_AXLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_AXLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_AXLabel, -25);
    lv_obj_set_y(ui_AXLabel, -55);
    lv_obj_set_align(ui_AXLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_AXLabel, "X - ");

    lv_obj_add_event_cb(ui_SensorTest, ui_event_SensorTest, LV_EVENT_ALL, NULL);

    lv_timer_create(update_labels, 100, NULL); 

}
