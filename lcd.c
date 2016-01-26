

#include "lcd.h"


//-----------------------------------------------------------------------------
void delay_ms(uint8_t val) //0-255ms delay
{
while(val--) __delay_ms(1);
}


//-----------------------------------------------------------------------------
void lcd_init(void)
{
//init PINs
RS_PIN;
RS_L;

EN_PIN;
EN_L;

D4_PIN;
D4_L;

D5_PIN;
D5_L;

D6_PIN;
D6_L;

D7_PIN;
D7_L;

//BL_PIN;
//BL_ON; //backlight ON

//init LCD controller
delay_ms(20); //delay on power up
lcd_cmd(0b0011);
delay_ms(5); //wait for the instruction to complete
lcd_cmd(0b0011);
__delay_us(200); //wait for the instruction to complete
lcd_cmd(0b0011);
__delay_us(200);
lcd_cmd(0b0010); //enable 4-bit mode
__delay_us(50);
lcd_cmd(0b0010);
lcd_cmd(0b1000); //4-bit mode, 2-line, 5x8 font
__delay_us(50);
lcd_cmd(0b0000);
lcd_cmd(0b1000); //display off
__delay_us(50);
lcd_clear();
lcd_cmd(0b0000);
lcd_cmd(0b0110); //entry mode set
__delay_us(50);
lcd_cmd(0b0000);
lcd_cmd(0b1100); //display on, cursor off, blink off
__delay_us(50);
}


//-----------------------------------------------------------------------------
void lcd_write(uint8_t data) //write data to LCD
{
if(data & 1) D4_H;
else D4_L;
	
if(data & 2) D5_H;
else D5_L;
	
if(data & 4) D6_H;
else D6_L;
	
if(data & 8) D7_H;
else D7_L;

EN_H;
__delay_us(100);
EN_L;
}


//-----------------------------------------------------------------------------
void lcd_cmd(uint8_t data) //send command to LCD
{ 
RS_L;
lcd_write(data);
}


//-----------------------------------------------------------------------------
void lcd_clear(void) //clear screen
{
lcd_cmd(0b0000);
lcd_cmd(0b0001);
delay_ms(5);
}


//-----------------------------------------------------------------------------
void lcd_goto(uint8_t line, uint8_t column) //line 0..1, column 0..39
{
lcd_cmd(((0x80+(line<<6))+column)>>4);
lcd_cmd((0x80+(line<<6))+column);
}


//-----------------------------------------------------------------------------
void lcd_char(uint8_t sign) //print a character
{
RS_H;
lcd_write(sign>>4);
lcd_write(sign);
}


//-----------------------------------------------------------------------------
void lcd_print(const char *str) //print a string
{
while(*str) lcd_char(*str++);
}


//-----------------------------------------------------------------------------
void lcd_right(void) //shift right 
{
lcd_cmd(0x01);
lcd_cmd(0x0C);
}


//-----------------------------------------------------------------------------
void lcd_left(void) //shift left
{
lcd_cmd(0x01);
lcd_cmd(0x08);
}
