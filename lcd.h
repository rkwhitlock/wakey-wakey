/**
 * Sources:
 *
 * ChatGPT (OpenAI): Assisted in generating and debugging LCD interface
 *
 */

// lcd.h: LCD screen output interface

#ifndef LCD_H
#define LCD_H

#include "shared.h"

// Definitions for LCD pins
#define LCD_RS 7  // Register Select pin
#define LCD_E 21  // Enable pin
#define LCD_D4 22 // Data pin 4
#define LCD_D5 23 // Data pin 5
#define LCD_D6 24 // Data pin 6
#define LCD_D7 25 // Data pin 7

// Pulses the enable pin
void pulseEnable();

// Sends a byte to the LCD
void lcd_byte(char bits);

// Sets the LCD to command mode
void SetCmdMode();

// Sets the LCD to character mode
void SetChrMode();

// Writes a string to LCD
void lcd_text(char *s);

// Initializes LCD
void lcd_init();

// Displays a string on LCD at a specific position
void display(char *s, char byte);

#endif