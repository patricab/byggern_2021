#ifndef CAN_BUS_H
#define CAN_BUS_H

typedef struct { // Define the can message structure
	unsigned int id; // lower ID, higher priority
	// Ex. can_message.id = 0x0;
	uint8_t length; // Byte amount of data
	char data[8]; // Max 8 bytes.
	// ex. can_message.data[n] = 'X';
} can_struct;

/**
 * @brief Initialize communication on CAN-bus
 * 
 */
void can_bus_init();

/**
 * @brief Define can_struct first. can_struct can_message. Ex. can_transmit(&can_message, 0);
 * 
 * @param message 
 */
void can_transmit(can_struct* can_message, uint8_t buffer_number);

/**
 * @brief Ex. can_struct message = can_recieve(0); Get data: message.data[n]
 * 
 * @return can_struct 
 */
can_struct can_receive(uint8_t buffer_number);
#endif