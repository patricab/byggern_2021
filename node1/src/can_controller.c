#include <avr/io.h>
#include <can_controller.h>
#include <spi.h>


#define DD_SS PB4

void can_controller_reset(void)
    {
        PORTB &= ~(1<<DD_SS); // Select CAN-controller
        spi_transmit(MCP_RESET); // Reset CAN-controller
        PORTB |= (1<<DD_SS); // Deselect CAN-controller
    }

uint8_t can_controller_init()
    {
        spi_init(); // Initialize SPI
        can_controller_reset(); // Send reset - command
        can_controller_bit_modify(MCP_CANCTRL, 0b11100000, MODE_CONFIG);
        // Self-test
        uint8_t value = can_controller_read(MCP_CANSTAT);
        printf("   CAN status: ");
		//uart_tx(value);
		printf("%c (%x)\n\r", value, value);
        if ((value & MODE_MASK) != MODE_CONFIG) {
            printf ("MCP2515 is NOT in configuration mode after reset !\n\r");
            return 1;
        }
        // More initialization
        return 0;
    }

uint8_t can_controller_read(uint8_t address)
    {
        uint8_t result;
        PORTB &= ~(1<<DD_SS); // Select CAN - controller
        spi_transmit(MCP_READ); // Send read instruction
        spi_transmit(address); // Send address
        result = spi_read(); // Read result
        PORTB |= (1<<DD_SS); // Deselect CAN - controller
        return result;
    }

void can_controller_write(uint8_t address, uint8_t data)
    {
        PORTB &= ~(1<<DD_SS); // Select CAN - controller
        spi_transmit(MCP_WRITE); // Send write instruction
        spi_transmit(address); // Send adress
        spi_transmit(data); // Send data
        PORTB |= (1<<DD_SS); // Deselect CAN - controller
    }

void can_controller_rts(uint8_t tx_buffer_nr) // RTS: Request to send data
    {
        PORTB &= ~(1<<DD_SS); // Select CAN - controller
        uint8_t req;
        if (tx_buffer_nr == 0) {
            req = MCP_RTS_TX0;
        }
        else if (tx_buffer_nr == 1) {
            req = MCP_RTS_TX1;
        }
        else if (tx_buffer_nr == 2) {
            req = MCP_RTS_TX2;
        }
        spi_transmit(req); // Send the request
        PORTB |= (1<<DD_SS); // Deselect CAN - controller
    }

uint8_t can_controller_read_status(void)
    {
        PORTB &= ~(1<<DD_SS); // Select CAN - controller
        spi_transmit(MCP_READ_STATUS);
        uint8_t status = spi_read(); // Get the status
        PORTB |= (1<<DD_SS); // Deselect CAN - controller
    }

void can_controller_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
    {
        PORTB &= ~(1<<DD_SS); // Select CAN - controller
        spi_transmit(MCP_BITMOD);
        spi_transmit(address);
        spi_transmit(mask);
        spi_transmit(data);
        PORTB |= (1<<DD_SS); // Deselect CAN - controller
    }

uint8_t can_error(void){
	uint8_t err = can_controller_read(MCP_EFLG);
    return err;

	// uint8_t mask = 0b00100000;
	// if (mask & err == mask){
	// 	printf("Error in CAN!\n");
	// 	can_controller_bit_modify(MCP_CANINTF,mask,0);
	// 	return 1;
	// }
	// return 0;
}
