#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"

#include "sam.h"
#include <bit.h>


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    // configure_uart();

    /* Enable PIO on bit PC2(D0) */
    set_bit(PIOC->PIO_PER, PIO_PC2);
    /* Set peripheral A on PC2(D0) */
    clear_bit(PIOC->PIO_ABSR, PIO_PC2);
    /* Set output enable on PC2(D0) */
    set_bit(PIOC->PIO_OER, PIO_PC2);

    while (1)
    {
        /* Toggle PC2(D0) */
        set_bit(PIOC->PIO_SODR, PIO_PC2);
        int i = 0;
        while (i < 10000) {i++;}
        set_bit(PIOC->PIO_CODR, PIO_PC2);
    }
    
}