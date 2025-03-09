#include "joystick.h"
#include "shared.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define DEADZONE 100 // Deadzone threshold for joystick movement

extern pthread_mutex_t board_lock;

int readADC(int channel)
{
    uint8_t buffer[3];
    buffer[0] = 1;                  // Start bit
    buffer[1] = (8 + channel) << 4; // Single-ended mode
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

    return ((buffer[1] & 3) << 8) + buffer[2]; // 10-bit ADC value (0-1023)
}

void *body_joystick(SharedVariable *v)
{
    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
    {
        printf("SPI setup failed!\n");
        pthread_exit(NULL);
    }

    pinMode(JOY_BTN_PIN, INPUT);
    pullUpDnControl(JOY_BTN_PIN, PUD_UP);

    while (!v->exit_flag)
    {
        int joyX = readADC(JOY_X_CH);
        int joyY = readADC(JOY_Y_CH);
        int buttonState = digitalRead(JOY_BTN_PIN);

        pthread_mutex_lock(&v->lock);

        if (joyX < (512 - DEADZONE) && v->cursor_x > 0)
        {
            v->cursor_x--;
        }
        else if (joyX > (512 + DEADZONE) && v->cursor_x < SIZE - 1)
        {
            v->cursor_x++;
        }

        if (joyY < (512 - DEADZONE) && v->cursor_y > 0)
        {
            v->cursor_y--;
        }
        else if (joyY > (512 + DEADZONE) && v->cursor_y < SIZE - 1)
        {
            v->cursor_y++;
        }

        pthread_mutex_unlock(&v->lock);

        if (buttonState == LOW)
        {
            printf("Joystick Button Pressed!\n");
        }

        delay(200);
    }

    pthread_exit(NULL);
}
