#include <stdio.h>
#include <stdarg.h>

#include "sam.h"
#include "uart.h"
#include <pwm.h>
#include <printf-stdarg.h>
#include <can_controller.h>

int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    /* Initialize libraries */
    configure_uart();
    pwm_init();
    can_init_def_tx_rx_mb();

    // /* Disable pull-up on bit PC2(D0) */
    // PIOA->PIO_PUDR |= PIO_PA19;
    // /* Enable PIO controller on bit PC2(D0) */
    // PIOA->PIO_PER |= PIO_PA19;
    // /* Set output enable on PC2(D0) */
    // PIOA->PIO_OER |= PIO_PA19;
    
    CAN_MESSAGE msg;
    while (1)
    {
    //     /* Toggle PC2(D0) */
    //     int i = 0;
    //     while (i < 1000000) {i++;}
    //     PIOA->PIO_SODR |= PIO_PA19;
    //     i = 0;
    //     while (i < 1000000) {i++;}
    //     PIOA->PIO_CODR |= PIO_PA19;
        // printf("Test\r\n", 0);
        
        /* Recieve can data and send to servo */
        can_receive(&msg, 0);
        pwm_run((int)msg.data);
        
    }
    
}