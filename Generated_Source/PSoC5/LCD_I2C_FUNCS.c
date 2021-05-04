/****************************************************************************
* This file is part of the PCF8574AT Custom Component for PSoC Devices.
*
* Copyright (C) 2017 Carlos Diaz <carlos.santiago.diaz@gmail.com>
*
* Based on the port of: Šarūnas Straigis
* http://www.element14.com/community/people/sarunaszx/blog
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
****************************************************************************/
    
#include <cytypes.h>
#include <cyfitter.h>

#include "project.h"

#include <stdint.h>
#include <string.h>

#include "LCD_I2C_REGS.h"
#include "LCD_I2C_LL_I2C.h"
#include "LCD_I2C_FUNCS.h"

struct LCD_I2C_Config LCD_I2C_config;

/*
uint8_t LCD_I2C_addr;
uint8_t LCD_I2C_displayfunction;
uint8_t LCD_I2C_displaycontrol;
uint8_t LCD_I2C_displaymode;
uint8_t LCD_I2C_cols;
uint8_t LCD_I2C_rows;
uint8_t LCD_I2C_charsize;
uint8_t LCD_I2C_backlightval;
*/

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1
//    S = 0; No shift 
void LCD_I2C_start(void)
{
    LCD_I2C_config.addr = 39;
    LCD_I2C_config.cols = 16;
    LCD_I2C_config.rows = 2;
    LCD_I2C_config.charsize = 0;
    LCD_I2C_config.backlightval = LCD_BACKLIGHT;
	LCD_I2C_config.displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

	if (LCD_I2C_config.rows > 1) {
		LCD_I2C_config.displayfunction |= LCD_2LINE;
	}

	// for some 1 line displays you can select a 10 pixel high font
	if ((LCD_I2C_config.charsize != 0) && (LCD_I2C_config.rows == 1)) {
		LCD_I2C_config.displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	CyDelay(50);
    
    LCD_I2C_begin();
}

void LCD_I2C_begin(void)
{
	// Now we pull both RS and R/W low to begin commands
    // reset expanderand turn backlight off (Bit 8 =1)
	LCD_I2C_expanderWrite(LCD_I2C_config.backlightval);
	CyDelay(1000);

	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	// we start in 8bit mode, try to set 4 bit mode
	LCD_I2C_write4bits(0x03 << 4);
	CyDelayUs(4500); // wait min 4.1ms

	// second try
	LCD_I2C_write4bits(0x03 << 4);
	CyDelayUs(4500); // wait min 4.1ms

	// third go!
	LCD_I2C_write4bits(0x03 << 4); 
	CyDelayUs(150);

	// finally, set to 4-bit interface
	LCD_I2C_write4bits(0x02 << 4); 

	// set # lines, font size, etc.
	LCD_I2C_command(LCD_FUNCTIONSET | LCD_I2C_config.displayfunction);  
	
	// turn the display on with no cursor or blinking default
	LCD_I2C_config.displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	LCD_I2C_display();
	
	// clear it off
	LCD_I2C_clear();
	
	// Initialize to default text direction (for roman languages)
	LCD_I2C_config.displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	LCD_I2C_command(LCD_ENTRYMODESET | LCD_I2C_config.displaymode);
	
	LCD_I2C_home();
}

/********** high level commands, for the user! */
void LCD_I2C_clear(void)
{
	LCD_I2C_command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	CyDelay(2);  // this command takes a long time!
}

void LCD_I2C_home(void)
{
    LCD_I2C_command(LCD_RETURNHOME);  // set cursor position to zero
	CyDelay(2);  // this command takes a long time!
}

void LCD_I2C_setCursor(uint8_t col, uint8_t row)
{
	const uint8_t row_offsets[4] = { 0x00, 0x40, 0x14, 0x54 };
	if (row > LCD_I2C_config.rows) {
		row = LCD_I2C_config.rows - 1;    // we count rows starting w/0
	}
	LCD_I2C_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LCD_I2C_noDisplay(void)
{
    LCD_I2C_config.displaycontrol &= ~LCD_DISPLAYON;
	LCD_I2C_command(LCD_DISPLAYCONTROL | LCD_I2C_config.displaycontrol);
}

void LCD_I2C_display(void)
{
	LCD_I2C_config.displaycontrol |= LCD_DISPLAYON;
	LCD_I2C_command(LCD_DISPLAYCONTROL | LCD_I2C_config.displaycontrol);
}

// Turns the underline cursor on/off
void LCD_I2C_noCursor(void)
{
    LCD_I2C_config.displaycontrol &= ~LCD_CURSORON;
	LCD_I2C_command(LCD_DISPLAYCONTROL | LCD_I2C_config.displaycontrol);
}

void LCD_I2C_cursor(void)
{
    LCD_I2C_config.displaycontrol |= LCD_CURSORON;
	LCD_I2C_command(LCD_DISPLAYCONTROL | LCD_I2C_config.displaycontrol);
}

// Turn on and off the blinking cursor
void LCD_I2C_noBlink(void)
{
    LCD_I2C_config.displaycontrol &= ~LCD_BLINKON;
	LCD_I2C_command(LCD_DISPLAYCONTROL | LCD_I2C_config.displaycontrol);
}

void LCD_I2C_blink(void)
{
	LCD_I2C_config.displaycontrol |= LCD_BLINKON;
	LCD_I2C_command(LCD_DISPLAYCONTROL | LCD_I2C_config.displaycontrol);
}

// These commands scroll the display without changing the RAM
void LCD_I2C_scrollDisplayLeft(void)
{
	LCD_I2C_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_I2C_scrollDisplayRight(void)
{
    LCD_I2C_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LCD_I2C_leftToRight(void)
{
	LCD_I2C_config.displaymode |= LCD_ENTRYLEFT;
	LCD_I2C_command(LCD_ENTRYMODESET | LCD_I2C_config.displaymode);
}

// This is for text that flows Right to Left
void LCD_I2C_rightToLeft(void)
{
	LCD_I2C_config.displaymode &= ~LCD_ENTRYLEFT;
	LCD_I2C_command(LCD_ENTRYMODESET | LCD_I2C_config.displaymode);
}

// This will 'right justify' text from the cursor
void LCD_I2C_autoscroll(void)
{
    LCD_I2C_config.displaymode |= LCD_ENTRYSHIFTINCREMENT;
	LCD_I2C_command(LCD_ENTRYMODESET | LCD_I2C_config.displaymode);
}

// This will 'left justify' text from the cursor
void LCD_I2C_noAutoscroll(void)
{
    LCD_I2C_config.displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	LCD_I2C_command(LCD_ENTRYMODESET | LCD_I2C_config.displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LCD_I2C_createChar(uint8_t location, uint8_t charmap[])
{
    location &= 0x7; // we only have 8 locations 0-7
	LCD_I2C_command(LCD_SETCGRAMADDR | (location << 3));
	for (uint32_t i = 0; i < 8; i++) {
		LCD_I2C_write(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void LCD_I2C_noBacklight(void)
{
    LCD_I2C_config.backlightval = LCD_NOBACKLIGHT;
	LCD_I2C_expanderWrite(0);
}

void LCD_I2C_backlight(void)
{
	LCD_I2C_config.backlightval = LCD_BACKLIGHT;
	LCD_I2C_expanderWrite(0);
}

void LCD_I2C_expanderWrite(uint8_t data)
{
	LCD_I2C_writeByte(LCD_I2C_config.addr, data | LCD_I2C_config.backlightval);
}

void LCD_I2C_write(uint8_t data)
{
	LCD_I2C_send(data, RS);
}

void LCD_I2C_command(uint8_t command)
{
    LCD_I2C_send(command, 0);
}

void LCD_I2C_print(const char *word)
{
    for (uint32_t i = 0; word[i] != '\0'; ++i) {
        LCD_I2C_write(word[i]);
    }
}

void LCD_I2C_setBacklight(bool backlight)
{
    backlight ? LCD_I2C_backlight() : LCD_I2C_noBacklight();
}

void LCD_I2C_loadCustomCharacter(uint8_t char_num, uint8_t *rows)
{
    LCD_I2C_createChar(char_num, rows);
}

void LCD_I2C_pulseEnable(uint8_t data)
{
    // EN high
	LCD_I2C_expanderWrite(data | EN);
    // enable pulse must be >450ns
	CyDelayUs(1);
    // En low
	LCD_I2C_expanderWrite(data & ~EN);
    // commands need > 37us to settle
	CyDelayUs(50);
}

// write either command or data
void LCD_I2C_send(uint8_t value, const uint8_t mode)
{
	uint8_t highnib = value & 0xf0;
	uint8_t lownib = (value << 4) & 0xf0;
	LCD_I2C_write4bits(highnib | mode);
	LCD_I2C_write4bits(lownib | mode);
}

void LCD_I2C_write4bits(const uint8_t data)
{    
	LCD_I2C_expanderWrite(data);
	LCD_I2C_pulseEnable(data);
}

/* [] END OF FILE */
