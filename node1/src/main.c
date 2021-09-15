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
#include <stdint.h>

#include <test.h>
#include <stdio.h>
#include <uart.h>
#include <bit.h>

int main(void)
{
	uart_init(9600);
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM

	// set PortC as output
	DDRC = 15;
	PORTC = 0x00;

	DDRA = 0xFF;
	PORTA = 0x00;


	

	// Enable external SRAM
	// set_bit(MCUCR, SRE);
	MCUCR |= (1 << SRE);

	// Set wait state
	EMCUCR |= (1 << SRW11);


	// Mask JTAG bits
	// set_bit(SFIOR, XMM2);
	SFIOR |= (1 << XMM2);

	SRAM_test();
    /* Replace with your applicatiWon code */
	
    while (1) 
    {
		PORTA |= (1 << PA2);
		PORTA |= (1 << PA0);
		_delay_ms(500);
		
		PORTA &= (0 << PA2);
		PORTA &= (0 << PA0);
		_delay_ms(500);
    }
}


