#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>
#include "drivers/RV3028/RV3028.h"

#define PASSWORD    0x20

extern struct tm CurrentTime;

extern rv3028_error_t ErrorCode;
extern rv3028_t RTC;
extern rv3028_init_t RTC_Init;

extern const struct device *i2c_dev;

void TWI_Init(void);

rv3028_error_t RV3028_Write(uint8_t Device_Addr, uint8_t Reg_Addr, const uint8_t *p_Reg_Data, uint32_t Length);
rv3028_error_t RV3028_Read(uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t *p_Reg_Data, uint32_t Length);
rv3028_error_t RV3028_Interface(rv3028_t* p_Device);
void start_clock(void);

