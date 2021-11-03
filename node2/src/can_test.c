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
    uint32_t can_br;
    can_br |= (0 << 24); // Incoming bit stream sampled once
    // can_br |= (41 << 16); // Baudrate prescaler = 41
    can_br |= (23 << 16); // Baudrate prescaler = 41
    can_br |= (1 << 12); // No re-synchronization jump width
    can_br |= (2 << 8); // Propagation segment of 2xTQ
    can_br |= (7 << 4); // Phase 1 at 7xTQ
    can_br |= 6; // Phase 2 at 6xTQ

    uint8_t ret = can_init_def_tx_rx_mb(can_br);
    if (ret > 0) {
        printf("Error: could not initialize CAN", 0);
    }
    
    CAN_MESSAGE msg;

    while (1)
    {
        
        // can_receive(&msg, 1);
        CAN0_Handler();
        printf("ID : %d\r\nLength: %d\r\nData: %s\r\n\n", msg.id, msg.data_length, msg.data);
        // printf("ID : %d\r\nLength: %d\r\nData: %s", msg.id, msg.data_length, "Test");
        // printf("Test", 0);
        delay(1000000);
    }
    
}