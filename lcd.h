// lcd.h

#ifndef LCD_H
#define LCD_H

#include "shared.h"

#define LCD_RS 7
#define LCD_E 21
#define LCD_D4 22
#define LCD_D5 23
#define LCD_D6 24
#define LCD_D7 25

void pulseEnable();
void lcd_byte(char bits);
void SetCmdMode();
void SetChrMode();
void lcd_text(char *s);
void lcd_init();
void display(char *s, char byte);

#endif