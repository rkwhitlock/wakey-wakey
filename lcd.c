/*
 * lcd.c:
 *	  Simple program to send a string to the LCD
 */

#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

void pulseEnable()
{
    digitalWrite(LCD_E, HIGH);
    delayMicroseconds(1); // Enable pulse must be > 450ns
    digitalWrite(LCD_E, LOW);
    delayMicroseconds(50); // Command delay
}

/*
  Send a byte to the LCD in two nibbles
*/
void lcd_byte(char bits)
{
    // Send higher nibble
    digitalWrite(LCD_D4, (bits & 0x10) >> 4);
    digitalWrite(LCD_D5, (bits & 0x20) >> 5);
    digitalWrite(LCD_D6, (bits & 0x40) >> 6);
    digitalWrite(LCD_D7, (bits & 0x80) >> 7);
    pulseEnable();

    // Send lower nibble
    digitalWrite(LCD_D4, (bits & 0x01));
    digitalWrite(LCD_D5, (bits & 0x02) >> 1);
    digitalWrite(LCD_D6, (bits & 0x04) >> 2);
    digitalWrite(LCD_D7, (bits & 0x08) >> 3);
    pulseEnable();
}

void SetCmdMode()
{
    digitalWrite(LCD_RS, LOW); // Set for commands
}

void SetChrMode()
{
    digitalWrite(LCD_RS, HIGH); // Set for characters
}

void lcd_text(char *s)
{
    while (*s)
        lcd_byte(*s++);
}

void lcd_init()
{
    wiringPiSetup(); // Use BCM numbering

    // Ensure LCD pins are set as OUTPUT
    pinMode(LCD_E, OUTPUT);
    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_D4, OUTPUT);
    pinMode(LCD_D5, OUTPUT);
    pinMode(LCD_D6, OUTPUT);
    pinMode(LCD_D7, OUTPUT);

    digitalWrite(LCD_E, LOW);
    digitalWrite(LCD_RS, LOW);
    digitalWrite(LCD_D4, LOW);
    digitalWrite(LCD_D5, LOW);
    digitalWrite(LCD_D6, LOW);
    digitalWrite(LCD_D7, LOW);

    // LCD Initialization sequence
    SetCmdMode();
    delay(50);

    lcd_byte(0x33);
    delay(5);
    lcd_byte(0x32);
    delay(5);
    lcd_byte(0x28);
    delay(5);
    lcd_byte(0x0C);
    delay(5);
    lcd_byte(0x06);
    delay(5);
    lcd_byte(0x01);
    delay(3);
}

void display(char *s, char byte)
{
    SetCmdMode();
    lcd_byte(byte);
    SetChrMode();
    lcd_text(s);
}
