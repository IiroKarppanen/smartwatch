// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: smartwatch_ui

#include "ui.h"
#include "../drivers/max30101/max30101.h"

void update_bpm(){
    char bpm_str[8]; 
    snprintf(bpm_str, sizeof(bpm_str), "%.2f", bpm);
    lv_label_set_text(ui_Label3, bpm_str);
}

void ui_Pulse_screen_init(void)
{
    ui_Pulse = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Pulse, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_set_style_bg_color(ui_Pulse, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Pulse, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image1 = lv_img_create(ui_Pulse);
    lv_img_set_src(ui_Image1, &ui_img_1111712444);
    lv_obj_set_width(ui_Image1, 46);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 48
    lv_obj_set_x(ui_Image1, -45);
    lv_obj_set_y(ui_Image1, -75);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label3 = lv_label_create(ui_Pulse);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, 5);
    lv_obj_set_y(ui_Label3, -77);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "-");
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container1 = lv_obj_create(ui_Pulse);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_width(ui_Container1, 184);
    lv_obj_set_height(ui_Container1, 1);
    lv_obj_set_x(ui_Container1, -2);
    lv_obj_set_y(ui_Container1, -45);
    lv_obj_set_align(ui_Container1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_outline_color(ui_Container1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Container1, 230, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_Container1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_Container1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chart1 = lv_chart_create(ui_Pulse);
    lv_obj_set_width(ui_Chart1, 208);
    lv_obj_set_height(ui_Chart1, 100);
    lv_obj_set_x(ui_Chart1, -18);
    lv_obj_set_y(ui_Chart1, 15);
    lv_obj_set_align(ui_Chart1, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart1, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(ui_Chart1, 30);
    lv_chart_set_range(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 140);
    lv_chart_set_range(ui_Chart1, LV_CHART_AXIS_SECONDARY_Y, 0, 140);
    lv_chart_set_div_line_count(ui_Chart1, 3, 4);
    lv_chart_set_zoom_x(ui_Chart1, 240);
    lv_chart_set_zoom_y(ui_Chart1, 240);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 0, 0, 0, false, 50);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
    lv_chart_series_t * ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0xFF3232),
                                                                 LV_CHART_AXIS_PRIMARY_Y);
    static lv_coord_t ui_Chart1_series_1_array[] = { 65, 65, 64, 63, 66, 67, 65, 62, 62, 62, 61, 60, 60, 64, 68, 72, 78, 78, 80, 80, 81, 79, 78, 78, 78, 66, 66, 65, 54, 65, 65, 65, 65, 65, 65, 65, 65, 65, 68, 69, 71, 72, 72 };
    lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, ui_Chart1_series_1_array);
    lv_obj_set_style_bg_color(ui_Chart1, lv_color_hex(0x3B3B3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chart1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Chart1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Chart1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_Chart1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_Chart1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_Chart1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_line_width(ui_Chart1, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui_Chart1, false, LV_PART_ITEMS | LV_STATE_DEFAULT);

    lv_obj_set_style_size(ui_Chart1, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_line_color(ui_Chart1, lv_color_hex(0xFFFFFF), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_Chart1, 220, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_Chart1, 1, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Chart1, lv_color_hex(0xFFFFFF), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Chart1, 220, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Chart1, &lv_font_montserrat_10, LV_PART_TICKS | LV_STATE_DEFAULT);

    ui_Label6 = lv_label_create(ui_Pulse);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, 44);
    lv_obj_set_y(ui_Label6, -77);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "BPM");
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Pulse, ui_event_Pulse, LV_EVENT_ALL, NULL);


    //lv_timer_create(update_bpm, 800, NULL); 
}
