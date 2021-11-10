
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <uart.h>
#include <stdio.h>
#include <spi.h>
#include <can_controller.h>
#include <can_bus.h>

int can_test(void) {
	uart_init(9600);
	printf("New upload!\n\r");

	can_bus_init(); // also initialize SPI
	can_struct can_message0;
	can_message0.id = 13;
	can_message0.length = 8;
	can_message0.data[0] = 'H';
	can_message0.data[1] = 'E';
	can_message0.data[2] = 'L';
	can_message0.data[3] = 'L';
	can_message0.data[4] = 'O';
	can_message0.data[5] = 'H';
	can_message0.data[6] = 'E';
	can_message0.data[7] = 'L';

	uint8_t buffer_0 = 0;


    while (1) 
    {
		can_controller_bit_modify(MCP_RXB0CTRL, 0b00001000, 0b00000000); // reset TXB0CTRL.TXREQ
		//can_transmit(&can_message0, buffer_0);
		_delay_ms(50);


		can_struct message0 = can_receive(0);
		_delay_ms(50);
		printf("   Data: ");
		for (int i = 0; i<message0.length; i++){
			uart_tx(message0.data[i]);
		}
		printf("   ID: ");
		printf("%u", message0.id);

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