#include <stdio.h>
#include <stdarg.h>

// #include "sam/sam3x/include/sam3x8e.h"
// #include "sam/sam3x/include/component/component_pio.h"
#include "sam.h"
// #include <bit.h>


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    // configure_uart();

    /* Enable PIO on bit PC2(D0) */
    // set_bit(PIOC->PIO_PER, PIO_PC2);
    PIOC->PIO_PER |= (1 << PIO_PC2);
    /* Set peripheral A on PC2(D0) */
    // clear_bit(PIOC->PIO_ABSR, PIO_PC2);
    PIOC->PIO_ABSR |= (0 << PIO_PC2);
    /* Set output enable on PC2(D0) */
    // set_bit(PIOC->PIO_OER, PIO_PC2);
    PIOC->PIO_OER |= (1 << PIO_PC2);

    while (1)
    {
        /* Toggle PC2(D0) */
        PIOC->PIO_SODR |= (1 << PIO_PC2);
        int i = 0;
        while (i < 10000) {i++;}
        PIOC->PIO_CODR |= (1 << PIO_PC2);
    }
    
}