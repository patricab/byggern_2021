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


    while (1) 
    {
		can_message0.id = 1;
		can_message0.length = 5;
		can_message0.data[0] = 'H';
		can_message0.data[1] = 'E';
		can_message0.data[2] = 'L';
		can_message0.data[3] = 'L';
		can_message0.data[4] = 'O';

		uint8_t buffer_0 = 0;

		can_controller_bit_modify(MCP_RXB0CTRL, 0b00001000, 0b00000000); // reset TXB0CTRL.TXREQ
		can_transmit(&can_message0, buffer_0);
		_delay_ms(50);


		// can_struct message0 = can_receive(0);
		// _delay_ms(50);
		// printf("   Data: ");
		// for (int i = 0; i<5; i++){
		// 	uart_tx(message0.data[i]);
		// }
		// printf("   ID: ");
		// printf("%u", message0.id);

		// MCP STATUS
		uint8_t status = can_controller_read(MCP_READ_STATUS);
		printf("   MCP status: ");
		printf("%c (%x)", status, status);
		// CAN STATUS
		uint8_t canstat = can_controller_read(MCP_CANSTAT);
		printf("   CAN status: ");
		printf("%c (%x)", canstat, canstat);
		// CAN ERRROR
		uint8_t error_check = can_error();
		printf("   Errors: ");
		printf("%x \n\r", error_check);
	}
}