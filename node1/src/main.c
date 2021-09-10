/*
 * Test_program.c
 *
 * Created: 01.09.2021 10:22:56
 * Author : andre
 */ 

#define F_CPU 16000000
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include <uart.h>
#include <bit.h>

int main(void)
{
    /* Replace with your application code */
	DDRA |= (1 << PA1);
	// sei();
	
	
    while (1) 
    {
		PORTA |= (1 << PA1);
		_delay_ms(500);
		
		PORTA &= (0 << PA1);
		_delay_ms(500);
		
		//test comment 2
		
		
		
    }
}
