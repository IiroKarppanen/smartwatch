SET(SOURCES screens/ui_mainMenu.c
    screens/ui_Home.c
    screens/ui_settingsMenu.c
    screens/ui_exerciseMenu.c
    screens/ui_Battery.c
    screens/ui_Pulse.c
    screens/ui_Brightness.c
    screens/ui_Time.c
    screens/ui_Date.c
    screens/ui_SensorTest.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_exercise1_png.c
    images/ui_img_headphones_png.c
    images/ui_img_heart_png.c
    images/ui_img_settings_icon_png.c
    images/ui_img_battery_full_png.c
    images/ui_img_battery_mid_png.c
    images/ui_img_clock_png.c
    images/ui_img_bluetooth_png.c
    images/ui_img_brightness_png.c
    images/ui_img_calendar_png.c
    images/ui_img_1111712444.c)

add_library(ui ${SOURCES})
