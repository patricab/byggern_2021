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
#include <can_bus.h>

int main(void)
{
	// ext_init();
	// sram_init();
	uart_init(9600);
	printf("New upload!\n\r");

	can_bus_init(); // also initialize SPI
	can_struct can_message0;
	can_struct can_message1;



	
    while (1) 
    {
		can_message0.id = 0x0;
		can_message0.length = 4;
		can_message0.data[0] = 'H';
		can_message0.data[1] = 'e';
		can_message0.data[2] = 'l';
		can_message0.data[3] = 'l';

		uint8_t buffer_0 = 0;

		can_transmit(&can_message0, buffer_0);
	
		_delay_ms(1000);
		// can_struct message0 = can_receive(buffer_0);
		// _delay_ms(500);
		// printf("   Data: ");
		// for (int i = 0; i<4; i++){
		// 	uart_tx(message0.data[i]);
		// }

		uint8_t value = can_controller_read(MCP_READ_STATUS);
		printf("   MCP status: ");
		//uart_tx(value);
		printf("%c (%x)", value, value);

		printf("   Test: ");
		uint8_t x = 'T';
		uart_tx(x);
		printf("x\n\r");
		_delay_ms(500);

	}
}