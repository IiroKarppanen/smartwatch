cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(Software)

#list(APPEND ZEPHYR_EXTRA_MODULES
#  ${CMAKE_CURRENT_SOURCE_DIR}/drivers/display/gc9a01
#  )

include_directories(src/)
include_directories(src/sensors)
include_directories(src/ui)
include_directories(src/drivers/input)
include_directories(src/drivers/input/cst816s)

#add_subdirectory(src/drivers)



target_sources(app PRIVATE 
src/main.c
src/drivers/max30101/algorithm.c
src/drivers/max30101/max30101.c
src/drivers/gc9a01/gc9a01.c
src/drivers/input/cst816d/input_cst816d.c
src/drivers/RV3028/RV3028.c
src/drivers/gnss/gnss.c
src/clock/clock.c


src/display_control/display_control.c
src/sensor_data/inertial_measurement.c
src/sensor_data/battery_gauge.c

)

file(GLOB_RECURSE ui_sources src/ui/*.c)
target_sources(app PRIVATE ${ui_sources})

file(GLOB_RECURSE sensor_sources src/sensors/*.c)
target_sources(app PRIVATE ${sensor_sources})


add_compile_definitions(LV_LVGL_H_INCLUDE_SIMPLE)