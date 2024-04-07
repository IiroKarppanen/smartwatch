// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: smartwatch_ui

#include "ui.h"

void ui_settingsMenu_screen_init(void)
{
    ui_settingsMenu = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_settingsMenu, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_settingsMenu, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image9 = lv_img_create(ui_settingsMenu);
    lv_img_set_src(ui_Image9, &ui_img_clock_png);
    lv_obj_set_width(ui_Image9, LV_SIZE_CONTENT);   /// 38
    lv_obj_set_height(ui_Image9, LV_SIZE_CONTENT);    /// 38
    lv_obj_set_x(ui_Image9, -61);
    lv_obj_set_y(ui_Image9, 33);
    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image10 = lv_img_create(ui_settingsMenu);
    lv_img_set_src(ui_Image10, &ui_img_bluetooth_png);
    lv_obj_set_width(ui_Image10, LV_SIZE_CONTENT);   /// 38
    lv_obj_set_height(ui_Image10, LV_SIZE_CONTENT);    /// 38
    lv_obj_set_x(ui_Image10, -65);
    lv_obj_set_y(ui_Image10, -62);
    lv_obj_set_align(ui_Image10, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image10, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image10, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image11 = lv_img_create(ui_settingsMenu);
    lv_img_set_src(ui_Image11, &ui_img_brightness_png);
    lv_obj_set_width(ui_Image11, LV_SIZE_CONTENT);   /// 38
    lv_obj_set_height(ui_Image11, LV_SIZE_CONTENT);    /// 38
    lv_obj_set_x(ui_Image11, -63);
    lv_obj_set_y(ui_Image11, -15);
    lv_obj_set_align(ui_Image11, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image11, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image11, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image12 = lv_img_create(ui_settingsMenu);
    lv_img_set_src(ui_Image12, &ui_img_calendar_png);
    lv_obj_set_width(ui_Image12, LV_SIZE_CONTENT);   /// 38
    lv_obj_set_height(ui_Image12, LV_SIZE_CONTENT);    /// 38
    lv_obj_set_x(ui_Image12, -1);
    lv_obj_set_y(ui_Image12, 73);
    lv_obj_set_align(ui_Image12, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image12, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image12, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_settingsMenu, ui_event_settingsMenu, LV_EVENT_ALL, NULL);

}
