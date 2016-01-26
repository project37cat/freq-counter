// Frequency counter  ver.:01  07-Jan-2016 - 15-Jan-2016
//
// "main.h" (file 2 of 4)
//
// MPLAB settigs for the Tiny Bootloader (reserved space in ROM):
// Project -> Build Options -> Global -> ROM ranges, add string: default,-7f30-07ff0
//
// Without the Config Bits


//for the built-in delay functions:
#define _XTAL_FREQ 48000000
//XTAL 12MHz x4 (PLL ENABLED) = 48MHz


typedef unsigned char uint8_t; //stdint
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;


char buff[41];
