#define F_CPU 4915200
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <uart.h>
#include <bit.h>

int test(void)
{
    /* Replace with your applicatiWon code */
	uart_init(9600);

    while (1) 
    {
		uart_tx('A');
		_delay_ms(1000);
		unsigned char rx = uart_rx(); // NOTE: Needs to be called by unsigned char!
		uart_tx(rx);
    }
}
