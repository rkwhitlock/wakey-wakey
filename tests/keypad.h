// keypad.h
#ifndef KEYPAD_H
#define KEYPAD_H

#include "shared.h"

#define ROWS 4
#define COLS 4

extern int rowPins[ROWS];
extern int colPins[COLS];
extern char keys[ROWS][COLS];

void setupKeypad();
char getKeyPress();
void *body_keypad(SharedVariable *v);

#endif