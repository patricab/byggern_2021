/*
 * Test_program.c
 *
 * Created: 01.09.2021 10:22:56
 * Author : andre
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


/*
#define set_bit ( reg , bit ) ( reg |= ( 1 << bit ) )
#define clear_bit ( reg , bit ) ( reg &= ˜ ( 1 << bit ) )
#define test_bit ( reg , bit ) ( reg & ( 1 << bit ) )
#define loop_until_bit_is_set ( reg , bit ) w hil e ( ! test_bit ( reg , bit ) )
#define loop_until_bit_is_clear ( reg , bit ) w hil e ( test_bit ( reg , bit ) )
#define toggle_bit ( reg , bit ) ( reg ^= ( 1 << bit ) )
*/

int main(void)
{
    /* Replace with your application code */
	DDRA |= (1 << PA1);
	sei();
	
	
    while (1) 
    {
		PORTA |= (1 << PA1);
		_delay_ms(500);
		
		PORTA &= (0 << PA1);
		_delay_ms(500);
		
		
		
		
    }
}

void USART_Transmit( unsigned char data ) //taken from the datasheet
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}