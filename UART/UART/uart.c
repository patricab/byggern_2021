#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <bit.h>
#include <uart.h>

int uart_tx(unsigned char data) //taken from the datasheet
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
    return 0;
}

unsigned char uart_rx(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}