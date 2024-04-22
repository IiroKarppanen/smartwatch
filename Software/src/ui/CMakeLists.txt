SET(SOURCES screens/ui_Home.c
    screens/ui_mainMenu.c
    screens/ui_settingsMenu.c
    screens/ui_GpsTest.c
    screens/ui_Battery.c
    screens/ui_Pulse.c
    screens/ui_Brightness.c
    screens/ui_Date.c
    screens/ui_SensorTest.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_lightning_green_png.c
    images/ui_img_steps16_png.c
    images/ui_img_exercise1_png.c
    images/ui_img_headphones_png.c
    images/ui_img_heart_png.c
    images/ui_img_settings_icon_png.c
    images/ui_img_battery_full_png.c
    images/ui_img_bluetooth_png.c
    images/ui_img_brightness_png.c
    images/ui_img_calendar_png.c
    images/ui_img_1111712444.c
    images/ui_img_heart16_png.c
    images/ui_img_heart20_png.c)

add_library(ui ${SOURCES})
