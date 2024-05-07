// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: smartwatch_ui

#ifndef _SMARTWATCH_UI_UI_H
#define _SMARTWATCH_UI_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "icons/icons.h" 
#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_Home
void ui_Home_screen_init(void);
void ui_event_Home(lv_event_t * e);
extern lv_obj_t * ui_Home;
extern lv_obj_t * ui_TimeLabel;
extern lv_obj_t * ui_monthLabel;
extern lv_obj_t * ui_dayNumberLabel;
extern lv_obj_t * ui_Arc12;
extern lv_obj_t * ui_Arc13;
extern lv_obj_t * ui_Label11;
extern lv_obj_t * ui_Image7;
extern lv_obj_t * ui_Image12;
// SCREEN: ui_powerManagment
void ui_powerManagment_screen_init(void);
void ui_event_powerManagment(lv_event_t * e);
extern lv_obj_t * ui_powerManagment;
extern lv_obj_t * ui_Switch4;
extern lv_obj_t * ui_Switch5;
extern lv_obj_t * ui_Label15;
extern lv_obj_t * ui_Label17;
// SCREEN: ui_mainMenu
void ui_mainMenu_screen_init(void);
void ui_event_mainMenu(lv_event_t * e);
extern lv_obj_t * ui_mainMenu;
void ui_event_Arc1(lv_event_t * e);
extern lv_obj_t * ui_Arc1;
extern lv_obj_t * ui_Arc2;
extern lv_obj_t * ui_Arc4;
extern lv_obj_t * ui_Arc5;
extern lv_obj_t * ui_Arc6;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_Image5;
extern lv_obj_t * ui_Image6;
extern lv_obj_t * ui_Image8;
// SCREEN: ui_settingsMenu
void ui_settingsMenu_screen_init(void);
void ui_event_settingsMenu(lv_event_t * e);
extern lv_obj_t * ui_settingsMenu;
void ui_event_Arc7(lv_event_t * e);
extern lv_obj_t * ui_Arc7;
void ui_event_Arc8(lv_event_t * e);
extern lv_obj_t * ui_Arc8;
void ui_event_Arc10(lv_event_t * e);
extern lv_obj_t * ui_Arc10;
void ui_event_Arc14(lv_event_t * e);
extern lv_obj_t * ui_Arc14;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label13;
extern lv_obj_t * ui_Label14;
void ui_event_Arc9(lv_event_t * e);
extern lv_obj_t * ui_Arc9;
// SCREEN: ui_GpsTest
void ui_GpsTest_screen_init(void);
void ui_event_GpsTest(lv_event_t * e);
extern lv_obj_t * ui_GpsTest;
extern lv_obj_t * ui_posLabel;
extern lv_obj_t * ui_utcLabel;
extern lv_obj_t * ui_statusLabel;

extern lv_obj_t * ui_Label_charge;

// SCREEN: ui_Battery
void ui_Battery_screen_init(void);
void ui_event_Battery(lv_event_t * e);
extern lv_obj_t * ui_Battery;
extern lv_obj_t * ui_Arc3;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Switch1;
extern lv_obj_t * ui_Label7;
// SCREEN: ui_Pulse
void ui_Pulse_screen_init(void);
void ui_event_Pulse(lv_event_t * e);
extern lv_obj_t * ui_Pulse;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Container1;
extern lv_obj_t * ui_Chart1;
extern lv_obj_t * ui_Label6;
// SCREEN: ui_Brightness
void ui_Brightness_screen_init(void);
void ui_event_Brightness(lv_event_t * e);
extern lv_obj_t * ui_Brightness;
extern lv_obj_t * ui_Slider1;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_BrightnessPercentage;
// SCREEN: ui_Date
void ui_Date_screen_init(void);
void ui_event_Date(lv_event_t * e);
extern lv_obj_t * ui_Date;
extern lv_obj_t * ui_Roller4;
extern lv_obj_t * ui_Roller5;
extern lv_obj_t * ui_Label9;
extern lv_obj_t * ui_Roller6;
extern lv_obj_t * ui_Label10;
extern lv_obj_t * ui_Slider2;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label8;
// SCREEN: ui_SensorTest
void ui_SensorTest_screen_init(void);
void ui_event_SensorTest(lv_event_t * e);
extern lv_obj_t * ui_SensorTest;
extern lv_obj_t * ui_Label12;
extern lv_obj_t * ui_AYLabel;
extern lv_obj_t * ui_AZLabel;
extern lv_obj_t * ui_Label16;
extern lv_obj_t * ui_GYLabel;
extern lv_obj_t * ui_GZLabel;
extern lv_obj_t * ui_GXLabel;
extern lv_obj_t * ui_AXLabel;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_lightning_green_png);    // assets\lightning_green.png
LV_IMG_DECLARE(ui_img_steps16_png);    // assets\steps16.png
LV_IMG_DECLARE(ui_img_exercise1_png);    // assets\exercise1.png
LV_IMG_DECLARE(ui_img_headphones_png);    // assets\headphones.png
LV_IMG_DECLARE(ui_img_heart_png);    // assets\heart.png
LV_IMG_DECLARE(ui_img_settings_icon_png);    // assets\settings_icon.png
LV_IMG_DECLARE(ui_img_battery_full_png);    // assets\battery_full.png
LV_IMG_DECLARE(ui_img_1111712444);    // assets\icons8-heart-48.png
LV_IMG_DECLARE(ui_img_heart16_png);    // assets\heart16.png
LV_IMG_DECLARE(ui_img_heart20_png);    // assets\heart20.png



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
