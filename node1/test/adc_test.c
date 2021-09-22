#define F_CPU 4915200

#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include <adc.h>
#include <uart.h>

int test(void)
{
    uart_init(9600);

    while (1)
    {
        char *read = adc_read();
        printf("%c\t%c\t%c\t%c\n", read[0], read[1], read[2], read[3]);
        _delay_ms(10);
    }
    
}