/**
 * Sources:
 *
 * ChatGPT (OpenAI): Assisted in generating getKeyPress() debounce and other key press read
 * handling to account for long presses
 *
 */

// keypad.h: keypad input interface

#ifndef KEYPAD_H
#define KEYPAD_H

#include "shared.h"

// Definitions for number and row pins
#define PIN_ONE 27
#define PIN_TWO 28
#define PIN_THREE 29
#define ROW_PIN 26

// Sets up wiring for keypad
void setupKeypad();

// Checks the keypad to see if a button has been pressed
int getKeyPress();

// Keypad handler that constantly reads keypad data and updates shared variable accordingly
void *body_keypad(SharedVariable *v);

#endif