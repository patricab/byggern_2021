#include <stdio.h>
#include <stdarg.h>

#include <test.h>

#include "sam.h"
#include "uart.h"
#include <can_controller.h>
#include <can_interrupt.h>

void delay(int ms) {
   int i = 0;
   while (i < ms){i++;}
}

void can_test(void) {
    /* Configure CAN baudrate register */

    uint8_t ret = can_init_def_tx_rx_mb();
    if (ret > 0) {
        printf("Error: could not initialize CAN", 0);
    }
    
    /* TX */
    // CAN_MESSAGE msg;
    // msg.id = 1;
    // msg.data_length = 2;
    // msg.data[0] = 'H';
    // msg.data[1] = 'i';

    /* RX */
    while (1)
    {
        can_receive(&msg, 0);
        printf("ID : %d\r\nLength: %d\r\nData: %s\r\n\n", msg.id, msg.data_length, msg.data);
        
        // printf("Test", 0);
        delay(1000000);
    }
    
}