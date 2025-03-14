// rtc.h
// Real Time Clock (RTC) interface
#ifndef RTC_H
#define RTC_H

#include "shared.h"

#define DS3231_I2C_ADDRESS 0x68
#define ALARM_HOUR 16 // Set alarm hour (24-hour format)
#define ALARM_MIN 59  // Set alarm minute

int bcdToDec(int val);            // Convert binary to decimal
void body_rtc(SharedVariable *v); // RTC handler

#endif