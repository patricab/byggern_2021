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
#include <can_controller.h>

int main(void)
{

	// ext_init();
	// sram_init();
	uart_init(9600);
	can_controller_init(); // also initialize SPI
	uint8_t result;

	
    while (1) 
    {
		can_controller_write(0xA7, 0x45);
		_delay_ms(50);
		result = can_controller_read(0xA7);
		_delay_ms(50);
		uart_tx(result);
		can_controller_write(0xA6, 0x53);
		_delay_ms(50);
		result = can_controller_read(0xA6);
		uart_tx(result);
		_delay_ms(50);
    }
}