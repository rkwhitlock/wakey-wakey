#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define DS3231_I2C_ADDRESS 0x68

int bcdToDec(int val) { return (val / 16 * 10) + (val % 16); }

int main()
{
    int fd = wiringPiI2CSetup(DS3231_I2C_ADDRESS);
    if (fd == -1)
    {
        fprintf(stderr, "Failed to initialize I2C communication.\n");
        return 1;
    }
    printf("DS3231 RTC Initialized\n");

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

        printf("Adjusted time: %04d-%02d-%02d %02d:%02d:%02d\n", adjusted_time->tm_year + 1900,
               adjusted_time->tm_mon + 1, adjusted_time->tm_mday, adjusted_time->tm_hour,
               adjusted_time->tm_min, adjusted_time->tm_sec);

        sleep(1);
    }
    return 0;
}
