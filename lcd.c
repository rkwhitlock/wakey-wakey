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
    // Pulses the enable pin to signal the LCD to read the data pins

    digitalWrite(LCD_E, HIGH);
    delayMicroseconds(1);
    digitalWrite(LCD_E, LOW);
    delayMicroseconds(50);
}

// Send byte to LCD
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

void SetCmdMode() { digitalWrite(LCD_RS, LOW); }

void SetChrMode() { digitalWrite(LCD_RS, HIGH); }

void lcd_text(char *s)
{
    // Write each character of string
    while (*s)
    {
        lcd_byte(*s);

        // Increment s to move to next character
        s++;
    }
}

void lcd_init()
{
    wiringPiSetup();

    // Set pins as output and write LOW default values
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
    // Set the position of where to write the string
    SetCmdMode();
    lcd_byte(byte);

    // Write the string
    SetChrMode();
    lcd_text(s);
}
