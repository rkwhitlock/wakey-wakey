#include "rtc.h"
#include "lcd.h"
#include "shared.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int bcdToDec(int val) { return (val / 16 * 10) + (val % 16); }

void body_rtc(SharedVariable *v)
{
    int fd = wiringPiI2CSetup(DS3231_I2C_ADDRESS);
    if (fd == -1)
    {
        fprintf(stderr, "Failed to initialize I2C communication.\n");
        return;
    }
    printf("DS3231 RTC Initialized\n");
    lcd_init();

    while (1)
    {
        wiringPiI2CWrite(fd, 0x00);
        int sec = bcdToDec(wiringPiI2CRead(fd));
        int min = bcdToDec(wiringPiI2CReadReg8(fd, 0x01));
        int hour = bcdToDec(wiringPiI2CReadReg8(fd, 0x02));
        int day = bcdToDec(wiringPiI2CReadReg8(fd, 0x04));
        int month = bcdToDec(wiringPiI2CReadReg8(fd, 0x05));
        int year = bcdToDec(wiringPiI2CReadReg8(fd, 0x06)) + 2000;

        // Use struct tm and mktime for proper time handling
        struct tm timeinfo = {0};
        timeinfo.tm_sec = sec;
        timeinfo.tm_min = min;
        timeinfo.tm_hour = hour;
        timeinfo.tm_mday = day;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_year = year - 1900;

        // Convert to time_t, adjust by subtracting 15 hours, and convert back
        time_t rawtime = mktime(&timeinfo);
        rawtime -= 16 * 3600;
        struct tm *adjusted_time = localtime(&rawtime);

        printf("Adjusted time: %04d-%02d-%02d %02d:%02d\n", adjusted_time->tm_year + 1900,
               adjusted_time->tm_mon + 1, adjusted_time->tm_mday, adjusted_time->tm_hour,
               adjusted_time->tm_min);

        char time_str[20];
        char date_str[20];

        snprintf(time_str, sizeof(time_str), "%02d:%02d", adjusted_time->tm_hour,
                 adjusted_time->tm_min);
        snprintf(date_str, sizeof(date_str), "%02d/%02d/%04d", adjusted_time->tm_mon + 1,
                 adjusted_time->tm_mday, adjusted_time->tm_year + 1900);

        display(time_str, 0x80);
        display(date_str, 0xC0);

        // Check if current time matches the alarm time
        if (adjusted_time->tm_hour == ALARM_HOUR && adjusted_time->tm_min == ALARM_MIN)
        {
            v->alarm = 1;
        }

        sleep(60); // Check time every minute
    }
}