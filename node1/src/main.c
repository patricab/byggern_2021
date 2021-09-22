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
#include <uart.h>
#include <ext.h>

int main(void)
{
	// adc_test();	
	uart_init(9600);
	ext_init();

	while (1)
	{
		ext_write(0x1800, 0x00, 'B');
		_delay_ms(100);
		uart_tx(ext_read(0x1800, 0x00));
		// volatile char *ext = 0x1800; // Set adress pointer
		// ext[0x00] = 'A';
		// _delay_ms(100);
		// uart_tx(ext[0x00]);
	}

	
//     while (1) 
//     {
// 		PORTB |= (1 << PB1);
// 		_delay_ms(500);
		
// 		PORTB &= (0 << PB1);
// 		_delay_ms(500);
//     }
}
