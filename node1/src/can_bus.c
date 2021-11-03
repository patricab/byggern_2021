#include <avr/io.h>
#include <can_bus.h>
#include <can_controller.h>
#include <uart.h>

void can_bus_init()
    {
        can_controller_init();
        can_controller_bit_modify(MCP_CANCTRL, 0b11100000, MODE_CONFIG);
        can_controller_bit_modify(MCP_CNF3, 0b11111111, 0b00000101); // Set bit timing
        can_controller_bit_modify(MCP_CNF2, 0b11111111, 0b10110001);
        can_controller_bit_modify(MCP_CNF1, 0b11111111, 0b00000011); // BRP

        can_controller_bit_modify(MCP_CANCTRL, 0b11100000, MODE_ONESHOT); //Set mode
        
        // INTERRUPT! FIX!
        // can_controller_write(MCP_CANINTE, MCP_RX_INT); // declare an interrupt for every message
    }


void can_transmit(can_struct* can_message, uint8_t buffer_number)
    {
        // Make MINIMUM CAN-message in buffer 0
        char id_high = can_message->id >> 3;
        char id_low = can_message->id << 5;

        uint8_t data_length = can_message->length;
        char* data = can_message->data; // char pointer points at 1 byte

        // Check buffer number
        if (buffer_number == 0) {
            can_controller_write(MCP_TXB0SIDH, id_high);
            can_controller_write(MCP_TXB0SIDL, id_low);
            can_controller_write(MCP_TXB0DLC, data_length);
            for (int i = 0; i < data_length; i++) {
                can_controller_write(MCP_TXB0D0+i, data[i]);
            }
        }
        if (buffer_number == 1) {
            can_controller_write(MCP_TXB1SIDH, id_high);
            can_controller_write(MCP_TXB1SIDL, id_low);
            can_controller_write(MCP_TXB1DLC, data_length);
            for (int i = 0; i < data_length; i++) {
                can_controller_write(MCP_TXB1D0+i, data[i]);
            }
        }
        // Request to send from buffer
        can_controller_rts(buffer_number); // RTS from buffer number
    }

can_struct can_receive(uint8_t buffer_number)
    {
        // choice for buffer number?

        // Receive from buffer 0
        can_struct can_message;

        // Check buffer number
        if (buffer_number == 0) {
            uint8_t id_high = can_controller_read(MCP_RXB0SIDH);
            uint8_t id_low = can_controller_read(MCP_RXB0SIDL);
            uint8_t mask = 0b11100000;
            id_low = (id_low & mask);
            can_message.id = 0b1000*id_high + id_low/0b100000;
            uint8_t data_length = can_controller_read(MCP_RXB0DLC);
            can_message.length = data_length;
            for (int i = 0; i < data_length; i++) {
                can_message.data[i] = can_controller_read(MCP_RXB0D0+i);
            }
            can_controller_bit_modify(MCP_CANINTF, 0b00000001, 0b0); // reset receive flag
        }
        if (buffer_number == 1) {
            uint8_t id_high = can_controller_read(MCP_RXB1SIDH);
            uint8_t id_low = can_controller_read(MCP_RXB1SIDL);
            uint8_t mask = 0b11100000;
            id_low = (id_low & mask);
            can_message.id = 0b1000*id_high + id_low/0b100000;
            uint8_t data_length = can_controller_read(MCP_RXB1DLC);
            can_message.length = data_length;
            for (int i = 0; i < data_length; i++) {
                can_message.data[i] = can_controller_read(MCP_RXB1D0+i);
            }
            can_controller_bit_modify(MCP_CANINTF, 0b00000010, 0b0); // reset receive flag
        }
        return can_message;
    }