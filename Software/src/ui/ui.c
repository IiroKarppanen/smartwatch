// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: smartwatch_ui

#include "ui.h"
#include "ui_helpers.h"


///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Home
void ui_Home_screen_init(void);
void ui_event_Home(lv_event_t * e);
lv_obj_t * ui_Home;
lv_obj_t * ui_TimeLabel;
lv_obj_t * ui_monthLabel;
lv_obj_t * ui_dayNumberLabel;
lv_obj_t * ui_Arc12;
lv_obj_t * ui_Arc13;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Image7;
lv_obj_t * ui_Image12;


// SCREEN: ui_powerManagment
void ui_powerManagment_screen_init(void);
void ui_event_powerManagment(lv_event_t * e);
lv_obj_t * ui_powerManagment;
lv_obj_t * ui_Switch4;
lv_obj_t * ui_Switch5;
lv_obj_t * ui_Label15;
lv_obj_t * ui_Label17;


// SCREEN: ui_mainMenu
void ui_mainMenu_screen_init(void);
void ui_event_mainMenu(lv_event_t * e);
lv_obj_t * ui_mainMenu;
void ui_event_Arc1(lv_event_t * e);
lv_obj_t * ui_Arc1;
lv_obj_t * ui_Arc2;
lv_obj_t * ui_Arc4;
lv_obj_t * ui_Arc5;
lv_obj_t * ui_Arc6;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Image4;
lv_obj_t * ui_Image5;
lv_obj_t * ui_Image6;
lv_obj_t * ui_Image8;


// SCREEN: ui_settingsMenu
void ui_settingsMenu_screen_init(void);
void ui_event_settingsMenu(lv_event_t * e);
lv_obj_t * ui_settingsMenu;
void ui_event_Arc7(lv_event_t * e);
lv_obj_t * ui_Arc7;
void ui_event_Arc8(lv_event_t * e);
lv_obj_t * ui_Arc8;
void ui_event_Arc10(lv_event_t * e);
lv_obj_t * ui_Arc10;
void ui_event_Arc14(lv_event_t * e);
lv_obj_t * ui_Arc14;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label13;
lv_obj_t * ui_Label14;
void ui_event_Arc9(lv_event_t * e);
lv_obj_t * ui_Arc9;


// SCREEN: ui_GpsTest
void ui_GpsTest_screen_init(void);
void ui_event_GpsTest(lv_event_t * e);
lv_obj_t * ui_GpsTest;
lv_obj_t * ui_posLabel;
lv_obj_t * ui_utcLabel;
lv_obj_t * ui_statusLabel;


// SCREEN: ui_Battery
void ui_Battery_screen_init(void);
void ui_event_Battery(lv_event_t * e);
lv_obj_t * ui_Battery;
lv_obj_t * ui_Arc3;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Switch1;
lv_obj_t * ui_Label7;


// SCREEN: ui_Pulse
void ui_Pulse_screen_init(void);
void ui_event_Pulse(lv_event_t * e);
lv_obj_t * ui_Pulse;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Container1;
lv_obj_t * ui_Chart1;
lv_obj_t * ui_Label6;


lv_obj_t * ui_Label_charge;


// SCREEN: ui_Brightness
void ui_Brightness_screen_init(void);
void ui_event_Brightness(lv_event_t * e);
lv_obj_t * ui_Brightness;
lv_obj_t * ui_Slider1;
lv_obj_t * ui_Label4;
lv_obj_t * ui_BrightnessPercentage;


// SCREEN: ui_Date
void ui_Date_screen_init(void);
void ui_event_Date(lv_event_t * e);
lv_obj_t * ui_Date;
lv_obj_t * ui_Roller4;
lv_obj_t * ui_Roller5;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Roller6;
lv_obj_t * ui_Label10;
lv_obj_t * ui_Slider2;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label8;


// SCREEN: ui_SensorTest
void ui_SensorTest_screen_init(void);
void ui_event_SensorTest(lv_event_t * e);
lv_obj_t * ui_SensorTest;
lv_obj_t * ui_Label12;
lv_obj_t * ui_AYLabel;
lv_obj_t * ui_AZLabel;
lv_obj_t * ui_Label16;
lv_obj_t * ui_GYLabel;
lv_obj_t * ui_GZLabel;
lv_obj_t * ui_GXLabel;
lv_obj_t * ui_AXLabel;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_exercise[1] = {&ui_img_exercise1_png};
const lv_img_dsc_t * ui_imgset_heart[2] = {&ui_img_heart16_png, &ui_img_heart20_png};
const lv_img_dsc_t * ui_imgset_1730909992[1] = {&ui_img_1111712444};
const lv_img_dsc_t * ui_imgset_steps[1] = {&ui_img_steps16_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Home(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_mainMenu, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_mainMenu_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Pulse, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Pulse_screen_init);
    }
}
void ui_event_powerManagment(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_SensorTest, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_SensorTest);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_GpsTest, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_GpsTest_screen_init);
    }
    
}
void ui_event_mainMenu(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Home, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Home_screen_init);
    }
}
void ui_event_Arc1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        (e);
    }
    if(event_code == LV_EVENT_RELEASED) {
        (e);
    }
}
void ui_event_settingsMenu(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Home, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Home_screen_init);
    }
}
void ui_event_Arc7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        (e);
    }
    if(event_code == LV_EVENT_RELEASED) {
        (e);
    }
}
void ui_event_Arc8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        (e);
    }
    if(event_code == LV_EVENT_RELEASED) {
        (e);
    }
}
void ui_event_Arc10(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        (e);
    }
    if(event_code == LV_EVENT_RELEASED) {
        (e);
    }
}
void ui_event_Arc14(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        (e);
    }
    if(event_code == LV_EVENT_RELEASED) {
        (e);
    }
}
void ui_event_Arc9(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        (e);
    }
    if(event_code == LV_EVENT_RELEASED) {
        (e);
    }
}
void ui_event_GpsTest(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_powerManagment, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_powerManagment_screen_init);
    }
}
void ui_event_Battery(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Home, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Home_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Home, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Home_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Home, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Home_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Home, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Home_screen_init);
    }
}
void ui_event_Pulse(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Home, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Home_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_SensorTest, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_SensorTest_screen_init);
    }
}
void ui_event_Brightness(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_mainMenu, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_mainMenu_screen_init);
    }
}
void ui_event_Date(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_mainMenu, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_mainMenu_screen_init);
    }
}
void ui_event_SensorTest(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Pulse, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_Pulse_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_powerManagment, LV_SCR_LOAD_ANIM_NONE, 5, 0, &ui_powerManagment_screen_init);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    //lv_disp_set_rotation(dispp, LV_DISP_ROT_90);

    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);


    
    lv_disp_set_theme(dispp, theme);
    ui_Home_screen_init();
    ui_powerManagment_screen_init();
    ui_mainMenu_screen_init();
    ui_settingsMenu_screen_init();
    ui_GpsTest_screen_init();
    ui_Battery_screen_init();
    ui_Pulse_screen_init();
    ui_Brightness_screen_init();
    ui_Date_screen_init();
    ui_SensorTest_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_powerManagment);

}
