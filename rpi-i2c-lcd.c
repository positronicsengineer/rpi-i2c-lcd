//Copyright (c) 2019 positronics.engineer at yandex dot com.
//Distributed under the terms of the MIT license.

/* Implemented from python script into C by using Raspberry Pi bcm2835 library  
 * References
 * https://bitbucket.org/MattHawkinsUK/rpispy-misc/raw/master/python/lcd_i2c.py
 * http://www.airspayce.com/mikem/bcm2835/
 * https://github.com/vinniefranco/rpi-hd44780
 */
 
#include <stdio.h>
#include <unistd.h>
#include <bcm2835.h>
#include <string.h>

#include "rpi-i2c-lcd.h"

int lcd_set_i2c(void)
{
    char buf;
	if (!bcm2835_i2c_begin())
	{
		printf("bcm2835_i2c_begin() failed!!!\n");
		return 1;
	}
	bcm2835_i2c_setSlaveAddress(I2C_ADDR);
	bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_2500); //100 kHz

	if (bcm2835_i2c_read(&buf, 1) != BCM2835_I2C_REASON_OK)
    {
		printf("No ACK from i2c device!!!\n");
		return 1;
	}    
	return 0;
}

void lcd_send_nibble(const uint8_t nibble)
{
	uint8_t buf;
	buf = nibble | EN;
	usleep(EN_CYCLE_DELAY);
	bcm2835_i2c_write((char*)&buf, 1); //set EN pin of i2c dev high for defined period
	usleep(EN_PULSE_WIDTH);

	buf = nibble & ~EN;
	bcm2835_i2c_write((char*)&buf, 1);
	usleep(EN_CYCLE_DELAY);
}

/* mode 0 LCD CMD instruction (use LCD_CMD definition)
 * mode 1 LCD Data instruction (use LCD_DATA definition)
 */
void lcd_send_byte(const uint8_t byte, uint8_t mode)
{
	uint8_t high_nibble = (mode) | (byte & 0xF0) | (LCD_BACKLIGHT & (~RW)); //keep backlight ON, since write operation AND with ~RW, RS is set by "mode" param
	uint8_t low_nibble = mode | ((byte << 4) & 0xF0) | (LCD_BACKLIGHT & (~RW));

	//LCD is in 4-bit mode, first MSB 4 bit, then LSB 4 bit
	lcd_send_nibble(high_nibble);
    usleep(CMD_DELAY);
	lcd_send_nibble(low_nibble);
    usleep(CMD_DELAY);
}

void lcd_init(void)
{
	lcd_send_byte(0b00110011, LCD_CMD); //Initialize
	usleep(INIT_DELAY);
	lcd_send_byte(0b00110010, LCD_CMD); //Initialize
	usleep(INIT_DELAY);
	lcd_send_byte(0b00000110, LCD_CMD); //Cursor move direction
	usleep(INIT_DELAY);
	lcd_send_byte(0b00001100, LCD_CMD); //Display On,Cursor Off, Blink Off
	usleep(INIT_DELAY);
	lcd_send_byte(0b00101000, LCD_CMD); //Data length, number of lines, font size
	usleep(INIT_DELAY);
	lcd_send_byte(0b00000001, LCD_CMD); //Clear screen
	usleep(INIT_DELAY);
}

void lcd_end (void)
{
    bcm2835_i2c_end();
}

/* Cursor goes to home also
 */
void lcd_clear_screen(void)
{
	lcd_send_byte(0b00000001, LCD_CMD);
    usleep(INIT_DELAY);
}

/* set cursor position
 * call before lcd_put_str() and lcd_put_char()
 * line 1,2
 * column 1,..,16
 */
void lcd_cursor_pos (const uint8_t line, const uint8_t column)
{
	uint8_t buf;
	if(line == 1)
	{
		buf = LCD_LINE_1 + column - 1;
		lcd_send_byte(buf, LCD_CMD);
	}
	else if (line == 2)
	{
		buf = LCD_LINE_2 + column - 1;
		lcd_send_byte(buf, LCD_CMD);
	}
	else
		printf("LCD cursor line param greater than 2!!!\n");
}

/* set cursor position before use
 */
void lcd_put_char(const char ch)
{
	lcd_send_byte(ch, LCD_DATA);
}

/* set cursor position before use
 */
void lcd_put_str(const char *str)
{
	if (strlen(str) <= LCD_WIDTH)
	{
		while (*str)
		{
			lcd_send_byte(*str, LCD_DATA);
			str++;
		}
	}
	else
		printf("Number of chars in string is gretaer than screen!!!\n");
}