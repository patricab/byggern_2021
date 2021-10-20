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

#include <test.h>
#include <uart.h>
#include <ext.h>
#include <sram.h>
#include <spi.h>
#include <can_controller.h>
#include <can_bus.h>

int main(void)
{
	// ext_init();
	// sram_init();
	uart_init(9600);
	printf("New upload!\n\r");

	can_bus_init(); // also initialize SPI
	can_struct can_message0;
	
    while (1) 
    {
		can_transmit(&can_message0, 0);
	}
}