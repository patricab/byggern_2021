/*
 * Test_program.c
 *
 * Created: 01.09.2021 10:22:56
 * Author : andre
 */ 

#define F_CPU 4915200
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <adc_test.h>

int main(void)
{
    // /* Replace with your application code */
	// DDRB |= (1 << PB1);
	// sei();
	adc_test();	
	
//     while (1) 
//     {
// 		PORTB |= (1 << PB1);
// 		_delay_ms(500);
		
// 		PORTB &= (0 << PB1);
// 		_delay_ms(500);
//     }
}
