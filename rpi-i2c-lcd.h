//Copyright (c) 2019 positronics.engineer at yandex dot com.
//Distributed under the terms of the MIT license.

#ifndef RPI_I2C_LCD_H
#define RPI_I2C_LCD_H

//Device parameters
#define I2C_ADDR  0x27 //I2C device address
#define LCD_WIDTH 16 //Maximum characters per line
#define LCD_LINE_1 0x80 //LCD RAM address for the 1st line
#define LCD_LINE_2 0xC0 //LCD RAM address for the 2nd line

//Mode definitions
#define LCD_DATA 1 //Sending data
#define LCD_CMD 0 //Sending command

#define RS 0b00000001  //P0 - PCF8574T Pin connected to RS of LCD, Register Select, 1 for data register operations, 0 for instrunction register operations
#define RW 0b00000010  //P1 - PCF8574T Pin connected to RW of LCD, Read/Write, 1 for read operation, 0 for write operations, this lib doesn't implement any read operations
#define EN 0b00000100  //P2 - PCF8574T Pin connected to EN of LCD, Enable, high pulse to enable given command
#define LCD_BACKLIGHT 0b00001000  //P3 - PCF8574T Pin connected to BACKLIGHT of LCD, 1 for ON, 0 for OFF

//Timing constants
#define EN_PULSE_WIDTH 1 //us
#define EN_CYCLE_DELAY 10 //us
#define CMD_DELAY 100 //us
#define INIT_DELAY 10000 //us

int lcd_set_i2c(void);

void lcd_init (void);
void lcd_end (void);

/* set cursor position
 * call before lcd_put_str() and lcd_put_char()
 * line 1,2
 * column 1,..,16
 */
void lcd_cursor_pos (const uint8_t line, const uint8_t column);

/* cursor also returns to home position
 * by lcd device itself
 */
void lcd_clear_screen (void);

/* send string to lcd
 * lenght of string must be less than LCD_WIDTH definition
 */
void lcd_put_str (const char *str);

/* send a single char to lcd
 */
void lcd_put_char (const char ch);

#endif //RPI_I2C_LCD_H