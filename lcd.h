// HD44780 2-line LCD library  b1 01-jan-2016 
//
// Compiler: HI-TECH C PRO for the PIC18 MCU Family  V9.63PL3


#include <htc.h>


#define _XTAL_FREQ 48000000


// define LCD lines connected to MCU's pins (can be used any pins)

// LCD line RW connected to Vss (ground)

// LCD line RS connected to RD6 pin
#define RS_PIN  TRISD6=0
#define RS_H    RD6=1
#define RS_L    RD6=0

// LCD line E connected to RD7 pin
#define EN_PIN  TRISD7=0
#define EN_H    RD7=1
#define EN_L    RD7=0

// LCD data bus (4-bit interface)
// data line 4..7 connected to RB0..RB3 pins
#define D4_PIN  TRISB0=0
#define D4_H    RB0=1
#define D4_L    RB0=0

#define D5_PIN  TRISB1=0
#define D5_H    RB1=1
#define D5_L    RB1=0

#define D6_PIN  TRISB2=0
#define D6_H    RB2=1
#define D6_L    RB2=0

#define D7_PIN  TRISB3=0
#define D7_H    RB3=1
#define D7_L    RB3=0

// LCD backlight line connected to RD5 pin
//#define BL_PIN  TRISD5=0
//#define BL_ON   RD5=1
//#define BL_OFF  RD5=0


typedef unsigned char uint8_t; //stdint
typedef unsigned int uint16_t;


void delay_ms(uint8_t val);

void lcd_init(void);
void lcd_write(uint8_t data);
void lcd_cmd(uint8_t data);
void lcd_clear(void);
void lcd_goto(uint8_t line, uint8_t column);
void lcd_char(uint8_t sign);
void lcd_print(const char *str);
void lcd_right(void);
void lcd_left(void);


