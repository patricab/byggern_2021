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

#include <test.h>
#include <bit.h>

int main(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM

	// Enable external SRAM
	// set_bit(MCUCR, SRE);
	MCUCR |= (1 << SRE);

	// Mask JTAG bits
	// set_bit(SFIOR, XMM2);
	SFIOR |= (1 << XMM2);

	
    while (1) 
    {
		SRAM_test();
    }
}
