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

    // /* Disable pull-up on bit PC2(D0) */
    // PIOC->PIO_PUDR |= PIO_PC2;
    // /* Enable PIO on bit PC2(D0) */
    // PIOC->PIO_PDR |= PIO_PC2;
    // /* Set peripheral A on PC2(D0) */
    // PIOC->PIO_ABSR &= ~PIO_PC2;
    // /* Set output enable on PC2(D0) */
    // PIOC->PIO_OER |= PIO_PC2;

    const uint8_t c = 't';
    while (1)
    {
        // /* Toggle PC2(D0) */
        // PIOC->PIO_SODR |= PIO_PC2;
        // int i = 0;
        // while (i < 10000) {i++;}
        // PIOC->PIO_CODR |= PIO_PC2;
        (void)uart_putchar(c);
    }
    
}