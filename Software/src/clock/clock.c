#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/init.h>
#include "drivers/RV3028/RV3028.h"
#include "clock.h"


struct tm CurrentTime = 
{
    .tm_sec = 0,
    .tm_min = 27,
    .tm_hour = 15,
    .tm_wday = 4,
    .tm_mday = 26,
    .tm_mon = 11,
    .tm_year = 20,
};

#define PASSWORD    0x20
#define CLOCK_THREAD_STACK_SIZE 1024
#define CLOCK_THREAD_PRIORITY 6

K_THREAD_STACK_DEFINE(clock_thread_stack, CLOCK_THREAD_STACK_SIZE);
struct k_thread clock_thread_data;

void clock_task()
{
    while (1) {
        
        RV3028_GetTime(&RTC, &CurrentTime);
        k_msleep(1000);  
    }
}



rv3028_error_t ErrorCode;
rv3028_t RTC;
rv3028_init_t RTC_Init = {
    .BatteryMode = RV3028_BAT_DSM,
    .Resistance = RV3028_TCT_3K,
    .EnableBSIE = true,
    .EnableCharge = true,

    .EnableTS = true,

    .Frequency = RV3028_CLKOUT_8KHZ,
    .EnableClkOut = true,

    .EnableEventInt = true,
    .EventHighLevel = false,
    .Filter = RV3028_FILTER_256HZ,

    .HourMode = RV3028_HOURMODE_24,
    .p_CurrentTime = &CurrentTime,

    .EnablePOR = false,

    .Password = PASSWORD,
};


const struct device *i2c_dev;


void TWI_Init(void)
{

    //i2c_dev = device_get_binding(I2C_DEV_NAME);      microcrystal,RV-3028-C7
    i2c_dev = device_get_binding("I2C_1");
    

    if (!i2c_dev) {
        printk("I2C device not found\n");
        return;
    }

}

rv3028_error_t RV3028_Write(uint8_t Device_Addr, uint8_t Reg_Addr, const uint8_t *p_Reg_Data, uint32_t Length)
{
    uint8_t Temp[8] = {Reg_Addr};

    for (uint8_t i = 0x01; i < (Length + 0x01); i++)
    {
        Temp[i] = *(p_Reg_Data++);
    }

    int ret = i2c_write(i2c_dev, Temp, Length + 0x01, Device_Addr);
    if (ret) {
        printk("I2C write error: %d", ret);
        return RV3028_COMM_ERROR;
    }

    return RV3028_NO_ERROR;
}

rv3028_error_t RV3028_Read(uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t *p_Reg_Data, uint32_t Length)
{
    struct i2c_msg msgs[2] = {
        {
            .buf = &Reg_Addr,
            .len = sizeof(Reg_Addr),
            .flags = I2C_MSG_WRITE,
        },
        {
            .buf = p_Reg_Data,
            .len = Length,
            .flags = I2C_MSG_READ,
        }
    };

    int ret = i2c_transfer(i2c_dev, &msgs[0], 2, Device_Addr);
    if (ret) {
        printk("I2C read error: %d", ret);
        return RV3028_COMM_ERROR;
    }

    return RV3028_NO_ERROR;
}


rv3028_error_t RV3028_Interface(rv3028_t* p_Device)
{
    if(p_Device == NULL)
    {
        return RV3028_INVALID_PARAM;
    }

    p_Device->p_Read = RV3028_Read;
    p_Device->p_Write = RV3028_Write;
    p_Device->DeviceAddr = RV3028_ADDRESS;

    return RV3028_NO_ERROR;
}


void start_clock(void){

    TWI_Init();

    ErrorCode = RV3028_Interface(&RTC);

    if (ErrorCode == RV3028_NO_ERROR)
    {
        RV3028_DisableWP(&RTC, PASSWORD);

        ErrorCode = RV3028_Init(&RTC_Init, &RTC);
        if (ErrorCode == RV3028_NO_ERROR)
        {
            printk("  HID: %u", RTC.HID);
            printk("  VID: %u", RTC.VID);

            k_sleep(K_MSEC(1000));
            printk("  Unlocking device...");
            RV3028_UnlockWP(&RTC, PASSWORD);
            RV3028_EnableClkOut(&RTC, false, false);

            RV3028_GetTime(&RTC, &CurrentTime);
            printk("  Current time: %u:%u:%u\n", CurrentTime.tm_hour, CurrentTime.tm_min, CurrentTime.tm_sec);
            k_sleep(K_MSEC(1000));

        }
        else
        {
            printk("Can not initialize RTC. Error: %u", ErrorCode);
        }
    }
    else
    {
        printk("Can not initialize RTC interface. Error: %u", ErrorCode);
    }


    // Create clock thread
    k_thread_create(&clock_thread_data, clock_thread_stack,
        K_THREAD_STACK_SIZEOF(clock_thread_stack),
        clock_task, NULL, NULL, NULL,
        CLOCK_THREAD_PRIORITY, 0, K_NO_WAIT);


}


SYS_INIT(start_clock, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);