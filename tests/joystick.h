// joystick.h
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "shared.h"

#define SPI_CHANNEL 0
#define SPI_SPEED 1000000
#define JOY_BTN_PIN 3
#define JOY_X_CH 0
#define JOY_Y_CH 1

int readADC(int channel);
void *body_joystick(SharedVariable *v);

#endif