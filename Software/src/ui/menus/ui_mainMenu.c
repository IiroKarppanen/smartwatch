// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: smartwatch_ui

#include "ui.h"

lv_obj_t * batteryButton;
lv_obj_t * settingsButton;
lv_obj_t * musicButton;
lv_obj_t * healthButton;
lv_obj_t * exerciseButton;

void custom_button_anim(void * var, int32_t value) {
    lv_obj_set_style_shadow_spread((lv_obj_t *)var, value, NULL);
    lv_obj_set_style_bg_opa((lv_obj_t *)var, (value*10), NULL);
}

void button_event_handler(lv_event_t * e)
{

    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);


    if(event_code == LV_EVENT_PRESSING) {
        lv_obj_set_style_shadow_spread(target, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(target, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    if(event_code == LV_EVENT_RELEASED || event_code == LV_EVENT_PRESS_LOST) {

        

        lv_anim_t shadow_fade_out;    
        lv_anim_init(&shadow_fade_out);
        lv_anim_set_exec_cb(&shadow_fade_out, custom_button_anim); 
        lv_anim_set_var(&shadow_fade_out, target); 
        lv_anim_set_time(&shadow_fade_out, 200);
        lv_anim_set_values(&shadow_fade_out, 5, 1);
        lv_anim_start(&shadow_fade_out);   

        
        if(target == batteryButton){
            _ui_screen_change(&ui_Battery, LV_SCR_LOAD_ANIM_NONE, 0, 0, NULL);
        }
        if(target == settingsButton){
           _ui_screen_change(&ui_settingsMenu, LV_SCR_LOAD_ANIM_NONE, 0, 0, NULL);
        }
        if(target == healthButton){
            _ui_screen_change(&ui_Pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, NULL);
        }
        if(target == musicButton){
            // Music screen not implemented yet
        }
        if(target == exerciseButton){
            // Exercise screen not implemented yet
        }
       
    }
    
}



void ui_mainMenu_screen_init(void)
{
    
    ui_mainMenu = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_mainMenu, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_mainMenu, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_mainMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Settings button 
    lv_obj_t * ui_settingsImage = lv_img_create(ui_mainMenu);
    lv_img_set_src(ui_settingsImage, &ui_img_settings_icon_png);
    lv_obj_set_width(ui_settingsImage, LV_SIZE_CONTENT);  
    lv_obj_set_height(ui_settingsImage, LV_SIZE_CONTENT);    
    lv_obj_set_x(ui_settingsImage, 76);
    lv_obj_set_y(ui_settingsImage, 22);
    lv_obj_set_align(ui_settingsImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settingsImage, LV_OBJ_FLAG_ADV_HITTEST);     
  
    settingsButton = lv_obj_create(ui_mainMenu);
    lv_obj_set_width(settingsButton, 68);
    lv_obj_set_height(settingsButton, 68);
    lv_obj_set_x(settingsButton, 76);
    lv_obj_set_y(settingsButton, 22);
    lv_obj_set_align(settingsButton, LV_ALIGN_CENTER);

    lv_obj_set_style_border_color(settingsButton, lv_color_hex(0xA4A4A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(settingsButton, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(settingsButton, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(settingsButton, lv_color_hex(0xA4A4A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(settingsButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(settingsButton, lv_color_hex(0xA4A4A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(settingsButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(settingsButton, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(settingsButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(settingsButton, button_event_handler, LV_EVENT_ALL, NULL);

    // battery button 
    lv_obj_t * ui_batteryImage = lv_img_create(ui_mainMenu);
    lv_img_set_src(ui_batteryImage, &ui_img_battery_full_png);
    lv_obj_set_width(ui_batteryImage, LV_SIZE_CONTENT);  
    lv_obj_set_height(ui_batteryImage, LV_SIZE_CONTENT);    
    lv_obj_set_x(ui_batteryImage, 0);
    lv_obj_set_y(ui_batteryImage, 79);
    lv_obj_set_align(ui_batteryImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_batteryImage, LV_OBJ_FLAG_ADV_HITTEST);     
  
    batteryButton = lv_obj_create(ui_mainMenu);
    lv_obj_set_width(batteryButton, 68);
    lv_obj_set_height(batteryButton, 68);
    lv_obj_set_x(batteryButton, 0);
    lv_obj_set_y(batteryButton, 79);
    lv_obj_set_align(batteryButton, LV_ALIGN_CENTER);

    lv_obj_set_style_border_color(batteryButton, lv_color_hex(0x7CFF9A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(batteryButton, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(batteryButton, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(batteryButton, lv_color_hex(0x7CFF9A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(batteryButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(batteryButton, lv_color_hex(0x7CFF9A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(batteryButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(batteryButton, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(batteryButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(batteryButton, button_event_handler, LV_EVENT_ALL, NULL);


    // music button 
    lv_obj_t * ui_musicImage = lv_img_create(ui_mainMenu);
    lv_img_set_src(ui_musicImage, &ui_img_headphones_png);
    lv_obj_set_width(ui_musicImage, LV_SIZE_CONTENT);  
    lv_obj_set_height(ui_musicImage, LV_SIZE_CONTENT);    
    lv_obj_set_x(ui_musicImage, -46);
    lv_obj_set_y(ui_musicImage, -64);
    lv_obj_set_align(ui_musicImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_musicImage, LV_OBJ_FLAG_ADV_HITTEST);     
  
    musicButton = lv_obj_create(ui_mainMenu);
    lv_obj_set_width(musicButton, 68);
    lv_obj_set_height(musicButton, 68);
    lv_obj_set_x(musicButton, -46);
    lv_obj_set_y(musicButton, -64);
    lv_obj_set_align(musicButton, LV_ALIGN_CENTER);

    lv_obj_set_style_border_color(musicButton, lv_color_hex(0x628EFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(musicButton, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(musicButton, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(musicButton, lv_color_hex(0x628EFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(musicButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(musicButton, lv_color_hex(0x628EFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(musicButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(musicButton, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(musicButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(musicButton, button_event_handler, LV_EVENT_ALL, NULL);


    // health button 
    lv_obj_t * ui_healthImage = lv_img_create(ui_mainMenu);
    lv_img_set_src(ui_healthImage, &ui_img_heart_png);
    lv_obj_set_width(ui_healthImage, LV_SIZE_CONTENT);  
    lv_obj_set_height(ui_healthImage, LV_SIZE_CONTENT);    
    lv_obj_set_x(ui_healthImage, -76);
    lv_obj_set_y(ui_healthImage, 22);
    lv_obj_set_align(ui_healthImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_healthImage, LV_OBJ_FLAG_ADV_HITTEST);     
  
    healthButton = lv_obj_create(ui_mainMenu);
    lv_obj_set_width(healthButton, 68);
    lv_obj_set_height(healthButton, 68);
    lv_obj_set_x(healthButton, -76);
    lv_obj_set_y(healthButton, 22);
    lv_obj_set_align(healthButton, LV_ALIGN_CENTER);

    lv_obj_set_style_border_color(healthButton, lv_color_hex(0xFF4B4B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(healthButton, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(healthButton, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(healthButton, lv_color_hex(0xFF4B4B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(healthButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(healthButton, lv_color_hex(0xFF4B4B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(healthButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(healthButton, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(healthButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(healthButton, button_event_handler, LV_EVENT_ALL, NULL);


    // exercise button 
    lv_obj_t * ui_exerciseImage = lv_img_create(ui_mainMenu);
    lv_img_set_src(ui_exerciseImage, &ui_img_exercise1_png);
    lv_obj_set_width(ui_exerciseImage, LV_SIZE_CONTENT);  
    lv_obj_set_height(ui_exerciseImage, LV_SIZE_CONTENT);    
    lv_obj_set_x(ui_exerciseImage, 46);
    lv_obj_set_y(ui_exerciseImage, -64);
    lv_obj_set_align(ui_exerciseImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_exerciseImage, LV_OBJ_FLAG_ADV_HITTEST);     
  
    exerciseButton = lv_obj_create(ui_mainMenu);
    lv_obj_set_width(exerciseButton, 68);
    lv_obj_set_height(exerciseButton, 68);
    lv_obj_set_x(exerciseButton, 46);
    lv_obj_set_y(exerciseButton, -64);
    lv_obj_set_align(exerciseButton, LV_ALIGN_CENTER);

    lv_obj_set_style_border_color(exerciseButton, lv_color_hex(0xFF40FA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(exerciseButton, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(exerciseButton, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(exerciseButton, lv_color_hex(0xFF40FA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(exerciseButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(exerciseButton, lv_color_hex(0xFF40FA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(exerciseButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(exerciseButton, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(exerciseButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(exerciseButton, button_event_handler, LV_EVENT_ALL, NULL);



    

    lv_obj_add_event_cb(ui_mainMenu, ui_event_mainMenu, LV_EVENT_ALL, NULL);

}
