#include "joystick.h"
#include "shared.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

int readADC(int channel)
{
    uint8_t buffer[3];

    // Start bit (1)
    buffer[0] = 1;

    // Single-ended mode (1) & channel selection
    buffer[1] = (8 + channel) << 4;

    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

    return ((buffer[1] & 3) << 8) + buffer[2];
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

    // Runs until sudoku is solved
    while (!v->sudoku_flag)
    {
        int joyX = readADC(JOY_X_CH);
        int joyY = readADC(JOY_Y_CH);
        int buttonState = digitalRead(JOY_BTN_PIN);

        pthread_mutex_lock(&v->lock);

        // Adjust cursor x and y values based on joystick
        if (joyX < (CENTER - DEADZONE) && v->cursor_x > 0)
        {
            v->cursor_x--;
        }
        else if (joyX > (CENTER + DEADZONE) && v->cursor_x < SIZE - 1)
        {
            v->cursor_x++;
        }

        if (joyY < (CENTER - DEADZONE) && v->cursor_y > 0)
        {
            v->cursor_y--;
        }
        else if (joyY > (CENTER + DEADZONE) && v->cursor_y < SIZE - 1)
        {
            v->cursor_y++;
        }

        pthread_mutex_unlock(&v->lock);

        // Clears sudoku cell if joystick button is pressed
        if (buttonState == LOW && !v->locked[v->cursor_y][v->cursor_x])
        {
            v->grid[v->cursor_y][v->cursor_x] = 0;
        }

        delay(200);
    }

    pthread_exit(NULL);
}
