#define F_CPU 4915200
// #define __AVR_ATmega162__

#include <avr/io.h>
#include <stdlib.h>
#include <bit.h>
#include <uart.h>

// Variables
// static int rx_count = 0;
// unsigned char rx_data[16] = {0};

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
	// Enable transmitter
	UCSR0B |= (1 << TXEN0);

	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));

	/* Put data into buffer, sends the data */
	UDR0 = data;

	// Disable transmitter
	UCSR0B |= (0 << TXEN0);

	// Check for empty transmit buffer
	if (!(UCSR0A & (1 << UDRE0)))
	{
		return 1;
	}

	return 0;
}

/**
  @brief Recieve data over UART

  @retval 0 if succesful, 1 if error occured
*/
int uart_rx(void) // Parts are copied from the Atmega162 datasheet!
{
	char rx_val;
	// // Clear RX buffer
	// memset(rx_data, 0, sizeof(rx_data));
	// // rx_data = {0};

	// // Enable reciever
	// UCSR0B |= (1 << RXEN0);

	// // Wait for EOT character or filled RX buffer
	// while (UDR0 != 0x04)
	// {
	// 	// Check for RX buffer overflow
	// 	if (rx_count > 16)
	// 	{
	// 		// Disable reciever
	// 		UCSR0B |= (0 << RXEN0);
	// 		return 1;
	// 	}

	// 	/* Wait for data to be received */
	// 	while (!(UCSR0A & (1 << RXC0)));

	// 	/* Get and return received data from buffer */
	// 	rx_data[rx_count] = UDR0;
	// 	rx_count = rx_count++;
	// }
	// // Reset RX counter
	// rx_count = 0;

	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	rx_val = UDR0;

	// Disable reciever
	UCSR0B |= (0 << RXEN0);
	
	// Enable transmitter
	UCSR0B |= (1 << TXEN0);

	uart_tx(rx_val);

	return 0;
}

/**
  @brief Initialize UART 

  @param baud Baudrate of UART transaction
*/
void uart_init(int baud) // Parts are copied from the Atmega162 datasheet!
{
	unsigned int ubrr = (F_CPU / (16 * baud)) - 1; // Register value for baud rate

	// Flush UART transmitter and reciever
	UCSR0B = (0 << RXEN0) | (0 << TXEN0);

	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}