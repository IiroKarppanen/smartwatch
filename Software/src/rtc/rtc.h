#ifndef RTC_H_
#define RTC_H_

#include <sys/printk.h>
#include <drivers/i2c.h>
#include <logging/log.h>
#include "driver/RV3028.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

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
void start_rtc(void);

#endif /* RTC_H_ */
