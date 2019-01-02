# Raspberry Pi I2C controlled LCD
`rpi-i2c-lcd` is a simple driver to control LCD attached to Raspberry Pi, over i2c port expander.  
- Supports write only operations for 2x16 dot matrix LCD.  
- Prints string and single characters to LCD screen. 
- Based on [bcm2835 library](http://www.airspayce.com/mikem/bcm2835/).  

### Usage
`#include "rpi-i2c-lcd.h"` in your code.  
Call `lcd_cursor_pos()` before `lcd_put_str()` and `lcd_put_char()`.  
See example `test-i2c-lcd.c`.  

### References
- Implemented from Python into C. [lcd_i2c.py](https://bitbucket.org/MattHawkinsUK/rpispy-misc/raw/master/python/lcd_i2c.py)  
- [GPIO based LCD lib](https://github.com/vinniefranco/rpi-hd44780)  
- [PCF8574 i2c port expander schematic](http://www.playembedded.org/blog/wp-content/uploads/2016/12/PCF8574-I2C-LCD-Schematic.jpg)  
- [Dot matrix LCD controller spec, HD44780](http://fab.cba.mit.edu/classes/863.06/11.13/44780.pdf)

### License
Distributed under the terms of the MIT license.  
Copyright (c) 2019 [positronics.engineer](https://github.com/positronicsengineer/) at yandex dot com.  