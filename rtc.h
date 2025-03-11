// rtc.h

#ifndef RTC_H
#define RTC_H

#include "shared.h"

#define DS3231_I2C_ADDRESS 0x68
#define ALARM_HOUR 17 // Set alarm hour (24-hour format)
#define ALARM_MIN 11  // Set alarm minute

int bcdToDec(int val);
void body_rtc(SharedVariable *v);

#endif