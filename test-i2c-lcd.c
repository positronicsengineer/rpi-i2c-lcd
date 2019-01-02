//Copyright (c) 2019 positronics.engineer at yandex dot com.
//Distributed under the terms of the MIT license.

#include <stdio.h>
#include <unistd.h>
#include <bcm2835.h>
#include "rpi-i2c-lcd.h"

int main(int argc, char** argv)
{
    const char *str1 = "Hello World";
    
    if (!bcm2835_init())
	{
		printf("bcm2835_init() failed. It must run by sudo!!!\n");
		return 1;
	}
    
    
    if (!lcd_set_i2c())
    {
        printf("lcd_set_i2c() failed!!!\n");
        return 1;
    }
    
    printf("Running LCD test...\n");
    lcd_init();
    
    //set string to first line
    lcd_cursor_pos(1,1);
    lcd_put_str(str1);
    
    //set cursor position and put char
    lcd_cursor_pos(2,1);
    lcd_put_char('R');
    
    lcd_cursor_pos(2,2);
    lcd_put_char('P');
    
    lcd_cursor_pos(2,3);
    lcd_put_char('i');
    
    lcd_cursor_pos(2,10);
    lcd_put_str(":-)");
    
    printf("Displaying test chars on LCD.\n" );
    sleep(10);

    //clear screen and finish tests
    lcd_clear_screen();
    lcd_put_str("Test OK, bye...");
    
    lcd_end();
    bcm2835_close();
    printf("Test finished.\n");
    return 0;
}
