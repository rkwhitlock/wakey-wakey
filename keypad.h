// keypad.h
#ifndef KEYPAD_H
#define KEYPAD_H

#include "shared.h"

#define SIZE 3

#define PIN_ONE 26
#define PIN_TWO 27
#define PIN_THREE 28
#define ROW_PIN 1

void setupKeypad();
int getKeyPress();
void *body_keypad(SharedVariable *v);

#endif