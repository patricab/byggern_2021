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
#include <sram.h>
#include <spi.h>

int main(void)
{

	// ext_init();
	// sram_init();
	uart_init(9600);
	spi_init();

	
    while (1) 
    {
		spi_transmit('U');
		_delay_ms(200);
		char x = spi_read();
		// printf("\r\n received:");
		// printf(x);
		_delay_ms(50);

    }
}