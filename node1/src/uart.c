#define F_CPU 16000000
// #define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <bit.h>
#include <uart.h>

/**
  @brief Transmit data throught UART

  @param data Data to be sent (8-bit)

  @retval 0 if succesful
*/
int uart_tx(unsigned char data) //taken from the datasheet
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
  
	/* Put data into buffer, sends the data */
	UDR0 = data;
  return 0;
}

unsigned char uart_rx(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
  
	/* Get and return received data from buffer */
	return UDR0;
}

/**
  @brief Initialize UART 

  @param baud Baudrate of UART transaction
*/
void uart_init(int baud) {
    unsigned int ubrr = (F_CPU/(16*baud))-1; // Register value for baud rate

	// Flush UART transmitter and reciever
    UCSR0B = (0<<RXEN0)|(0<<TXEN0);
    
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}