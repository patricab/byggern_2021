#include <stdio.h>
#include <stdarg.h>

#include "sam.h"
#include "uart.h"
#include <pwm.h>
#include <printf-stdarg.h>
#include <can_controller.h>
#include <adc.h>
#include <solonoid.h>

// void delay(int ms) {
//    int i = 0;
//    while (i < ms){i++;}
// }

int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    /* Initialize libraries */
    configure_uart();
    adc_init();
    pwm_init();
    solonoid_setup();

    uint8_t ret = can_init_def_tx_rx_mb();
    if (ret > 0) {
        printf("Error: could not initialize CAN", 0);
    }

    // /* Disable pull-up on bit PC2(D0) */
    // PIOA->PIO_PUDR |= PIO_PA19;
    // /* Enable PIO controller on bit PC2(D0) */
    // PIOA->PIO_PER |= PIO_PA19;
    // /* Set output enable on PC2(D0) */
    // PIOA->PIO_OER |= PIO_PA19;
    CAN_MESSAGE rx;
    CAN_MESSAGE tx = {
        .id = 2,
        .data_length = 1
    };
    
    while (1)
    {
    //     /* Toggle PC2(D0) */
    //     int i = 0;
    //     while (i < 1000000) {i++;}
    //     PIOA->PIO_SODR |= PIO_PA19;
    //     i = 0;
    //     while (i < 1000000) {i++;}
    //     PIOA->PIO_CODR |= PIO_PA19;
        
        /* Recieve can data and send to servo */
        can_receive(&rx, 0);
        // printf("ID : %d\r\nLength: %d\r\nData: %x %x\r\n\n", msg.id, msg.data_length, msg.data[0], msg.data[1]);
        printf("%d\r\n", rx.data[3]);

        // _Bool on = ir_on();
        // tx.data[0] = (char)on;

        // can_send(&tx, 0);
        // printf("%d\r\n", (int)on);

        // pwm_run((int)rx.data[0]);
        // run_solonoid((int)rx.data[2]);
    }
}