#include <stdio.h>
#include <stdarg.h>

// #include "sam/sam3x/include/sam3x8e.h"
// #include "sam/sam3x/include/component/component_pio.h"
#include "sam.h"
#include "uart.h"
// #include <bit.h>


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    configure_uart();

    /* Disable pull-up on bit PC2(D0) */
    PIOA->PIO_PUDR |= PIO_PA19;
    /* Enable PIO controller on bit PC2(D0) */
    PIOA->PIO_PER |= PIO_PA19;
    /* Set output enable on PC2(D0) */
    PIOA->PIO_OER |= PIO_PA19;

    // const uint8_t c = 's';
    while (1)
    {
        /* Toggle PC2(D0) */
        int i = 0;
        while (i < 1000000) {i++;}
        PIOA->PIO_SODR |= PIO_PA19;
        i = 0;
        while (i < 1000000) {i++;}
        PIOA->PIO_CODR |= PIO_PA19;
        // (void)uart_putchar(c);
    }
    
}