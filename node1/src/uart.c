#define F_CPU 4915200
#define __AVR_ATmega162__

#include <avr/io.h>
#include <stdlib.h>
#include <bit.h>
#include <uart.h>


/**
* NOTE: The scheema uses a 16 bit packet length, with 15 data bits, and a terminator 
* which uses an EOT (0x04) character
**/

/**
  @brief Send data over UART

  @param data Data to be sent

  @retval 0 if successful, 1 if errors occured
*/
int uart_tx(char data) // Parts are copied from the Atmega162 datasheet!
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));

	/* Put data into buffer, sends the data */
	UDR0 = data;

	return 0;
}

/**
  @brief Recieve data over UART

  @retval char Recieved character
*/
unsigned char uart_rx(void) // Parts are copied from the Atmega162 datasheet!
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)));

	/* Get and return received data from buffer */
	return UDR0;
}

/**
  @brief Initialize UART 

  @param baud Baudrate of UART transaction
*/
void uart_init(unsigned long baud) // Parts are copied from the Atmega162 datasheet!
{
	unsigned long clk = F_CPU;
	unsigned int ubrr = (clk / (16 * baud)) - 1; // Register value for baud rate

	// Enable UART transmitter and reciever
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);

	fdevopen(*uart_tx, *uart_rx);
}