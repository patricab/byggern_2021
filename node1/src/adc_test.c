#define F_CPU 4915200

#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include <adc.h>
#include <uart.h>

void adc_test(void)
{
    uart_init(9600);
    adc_init();

    while (1)
    {
        char *read = adc_read();
        uart_tx(read[0]);
        _delay_ms(100);
    }
    
}