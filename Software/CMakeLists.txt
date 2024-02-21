cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(Software)

#list(APPEND ZEPHYR_EXTRA_MODULES
#  ${CMAKE_CURRENT_SOURCE_DIR}/drivers/display/gc9a01
#  )

#add_subdirectory(drivers)
include_directories(src/)

target_sources(app PRIVATE 
src/main.c
src/drivers/gc9a01/gc9a01.c
#src/drivers/rtc/rtc.c
src/drivers/gc9a01/fonts/font8.c
src/drivers/gc9a01/fonts/font12.c
src/drivers/gc9a01/fonts/font16.c
src/drivers/gc9a01/fonts/font20.c
src/drivers/gc9a01/fonts/font24.c
)



