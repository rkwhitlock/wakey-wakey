// joystick.h
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "shared.h"
#include <wiringPi.h>

#define SPI_CHANNEL 0
#define SPI_SPEED 1000000
#define JOY_BTN_PIN 4
#define JOY_X_CH 0
#define JOY_Y_CH 1

#define DEADZONE 100 // Deadzone threshold for joystick movement

int readADC(int channel);
void *body_joystick(SharedVariable *v);

#endif