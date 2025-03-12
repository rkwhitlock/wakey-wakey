// keypad.h
#ifndef KEYPAD_H
#define KEYPAD_H

#include "shared.h"

#define SIZE 3

#define PIN_ONE 27
#define PIN_TWO 28
#define PIN_THREE 29
#define ROW_PIN 26

void setupKeypad();
int getKeyPress();
void *body_keypad(SharedVariable *v);

#endif