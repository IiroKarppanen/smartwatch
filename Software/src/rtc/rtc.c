#include <sys/printk.h>
#include <drivers/i2c.h>
#include <logging/log.h>
#include "driver/RV3028.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define PASSWORD    0x20

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

#define I2C_DEV_NAME DT_LABEL(DT_NODELABEL(i2c2))

static const struct device *i2c_dev;


void TWI_Init(void)
{
    i2c_dev = device_get_binding(I2C_DEV_NAME);
    if (!i2c_dev) {
        LOG_ERR("I2C device not found");
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
        LOG_ERR("I2C write error: %d", ret);
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
        LOG_ERR("I2C read error: %d", ret);
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


void start_rtc(void){


    printk("RV3028 RTC");
    TWI_Init();


    rv3028_t RTC;
    ErrorCode = RV3028_Interface(&RTC);
    if (ErrorCode == RV3028_NO_ERROR)
    {
        printk("RTC initialized...");
        RV3028_DisableWP(&RTC, PASSWORD);

        ErrorCode = RV3028_Init(&RTC_Init, &RTC);
        if (ErrorCode == RV3028_NO_ERROR)
        {
            printk("RTC initialized...");
            printk("  HID: %u", RTC.HID);
            printk("  VID: %u", RTC.VID);

            k_sleep(K_MSEC(1000));
            printk("  Unlocking device...");
            RV3028_UnlockWP(&RTC, PASSWORD);
            RV3028_EnableClkOut(&RTC, false, false);

            while (true)
            {
                uint8_t Status;
                uint8_t TSCount;
                struct tm LastTS;

                // Get the status flags
                RV3028_GetFlags(&RTC, &Status);
                printk("  Status: 0x%x", Status);

                // Check for a Power On Reset and clear the flag
                if (Status & RV3028_FLAG_POR)
                {
                    printk("  Power On Reset...");
                    RV3028_ClearFlags(&RTC, RV3028_FLAG_POR);
                }
                else if (Status & RV3028_FLAG_BATTERY)
                {
                    RV3028_ClearFlags(&RTC, RV3028_FLAG_BATTERY);
                    printk("  Battery switchover occurred...");

                    if (RTC.IsTSEnabled)
                    {
                        RV3028_GetTS(&RTC, &LastTS, &TSCount);
                        printk("  Last timestamp: %u:%u:%u", LastTS.tm_hour, LastTS.tm_min, LastTS.tm_sec);
                    }
                }
                else if (Status & RV3028_FLAG_EVENT)
                {
                    printk("  Event...");
                    RV3028_ClearFlags(&RTC, RV3028_FLAG_EVENT);

                    if (RTC.IsTSEnabled)
                    {
                        RV3028_GetTS(&RTC, &LastTS, &TSCount);
                        printk("  Last timestamp: %u:%u:%u", LastTS.tm_hour, LastTS.tm_min, LastTS.tm_sec);
                    }
                }

                RV3028_GetTime(&RTC, &CurrentTime);
                printk("  Current time: %u:%u:%u", CurrentTime.tm_hour, CurrentTime.tm_min, CurrentTime.tm_sec);

                k_sleep(K_MSEC(1000));
            }
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
}