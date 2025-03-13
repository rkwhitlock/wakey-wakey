/**
 * Sources:
 *
 * ChatGPT (OpenAI): Assisted in generating readADC() SPI channel reads
 *
 */

// joystick.h: joystick input interface

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "shared.h"
#include <wiringPi.h>

// Definitions for joystick input channels and pin
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000
#define JOY_BTN_PIN 4
#define JOY_X_CH 0
#define JOY_Y_CH 1

// Deadzone threshold for joystick movement
#define DEADZONE 100

// Center of joystick
#define CENTER 512

// Read from analog digital converter
int readADC(int channel);

// Joystick handler that constantly reads joystick data and updates shared variable
void *body_joystick(SharedVariable *v);

#endif