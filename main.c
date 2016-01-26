// Frequency counter
//
// "main.c" (file 1 of 4)


#include <htc.h>
#include <stdio.h>

#include "main.h"
#include "lcd.h"


//-----------------------------------------------------------------------------
void interrupt handler(void)
	{
	
	}
	
	
//-----------------------------------------------------------------------------
void delay_x10ms(uint8_t val)
	{
	while(val--) __delay_ms(10);
	}


//-----------------------------------------------------------------------------
void get_freq_1000ms(void)  //x1  //for 1000ms max. freq. 65535 Hz
	{
	TMR3IF=0; //clear timer3 overflow flag
	TMR3=0;   //clear timer3
	TMR3ON=1; //start frequency counter

	//accurate delay 1000ms
	delay_x10ms(100);
	__delay_ms(1);
	
	TMR3ON=0; //stop frequency counter
	}
	
	
//-----------------------------------------------------------------------------
void get_freq_100ms(void)  //x10  //for 100ms max. freq. 655.35 kHz (~0.65MHz)
	{
	TMR3IF=0; //clear timer3 overflow flag
	TMR3=0;   //clear timer3
	TMR3ON=1; //start frequency counter

	//accurate delay 100ms
	delay_x10ms(10);
	__delay_us(128);
	__delay_us(25);

	
	TMR3ON=0; //stop frequency counter
	}


//-----------------------------------------------------------------------------
void get_freq_10ms(void)  //"x100"  //for 10ms max. freq. 6.5535 kHz (~6.5MHz)
	{
	TMR3IF=0; //clear timer3 overflow flag
	TMR3=0;   //clear timer3
	TMR3ON=1; //start frequency counter

	//accurate delay 10ms
	delay_x10ms(1);
	__delay_us(10);
	NOP();
	NOP();
	
	TMR3ON=0; //stop freq. counter
	}


//-----------------------------------------------------------------------------
void get_freq_1ms(void)  //"x1000"  //for 1ms max. freq. 65535 kHz (~65MHz)  
	{
	TMR3IF=0; //clear timer3 overflow flag
	TMR3=0;   //clear timer3
	TMR3ON=1; //start frequency counter

	//accurate delay 1ms
	__delay_ms(1);
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	
	TMR3ON=0; //stop counter
	}
	

//-----------------------------------------------------------------------------	
void init_mcu(void)
	{
	ADCON1=0b1111; //disable analog inputs
	
	RBPU=1; //disable pull-up on PORTB
	
	//TMR0ON T08BIT T0CS T0SE PSA T0PS2 T0PS1 T0PS0
	T0CON=0b00000000;
	TMR0IE=0;
	
	// RD16 T1RUN T1CKPS1 T1CKPS0 T1OSCEN T1SYNC TMR1CS TMR1ON
	T1CON=0b00000000;
	TMR1IE=0;
	
	// — T2OUTPS3 T2OUTPS2 T2OUTPS1 T2OUTPS0 TMR2ON T2CKPS1 T2CKPS0
	T2CON=0b00000000;
	TMR2IE=0;
	
	//RD16 T3CCP2 T3CKPS1 T3CKPS0 T3CCP1 T3SYNC TMR3CS TMR3ON
	T3CON=0b00000110;
	TMR3IE=0;
	
	GIE=0; //disable interrupts
	PEIE=0;
	}


//-----------------------------------------------------------------------------
void main(void)
	{
	init_mcu();
		
	lcd_init();
	
	lcd_goto(0,3);
	lcd_print("v1");
	
	delay_x10ms(100);
	
	uint16_t freq=0;
	uint8_t range=0; //0-1000ms(x1), 1-100ms(x10), 2-10ms(x100), 3-1ms(x1000)

	while(1) //main loop
		{
		switch(range)
			{
			case 0:
				get_freq_1000ms(); //1sec. 0-65535 Hz  //"x1"
				freq = TMR3;
				if(TMR3IF==0) break;
				range=1;
			case 1:
				get_freq_100ms(); //0-655.35 kHz //"x10"
				freq = TMR3;
				if(freq<6500) range=0;
				if(TMR3IF==0) break;
				range=2;
			case 2:
				get_freq_10ms(); //0-6.5535 kHz  //"x100"
				freq = TMR3;
				if(freq<6500) range=1;
				if(TMR3IF==0) break;
				range=3;
			case 3:
				get_freq_1ms(); //0-65535 kHz  //"x1000"
				freq = TMR3;
				if(TMR3IF==1) freq=65535; //if timer overflow
				if(freq<6500) range=2;
				break;
			}
		
		sprintf(buff,"%5u",freq);
		lcd_goto(0,3);
		lcd_print(buff);
		
		lcd_goto(1,0);
		
		switch(range)
			{
			case 0: lcd_print("x1 Hz   "); break;
			case 1: lcd_print("x10 Hz  "); break;
			case 2: lcd_print("x100 Hz "); break;
			case 3: lcd_print("x1000 Hz"); break;
			}

		if(range) delay_x10ms(50);
		}

}
