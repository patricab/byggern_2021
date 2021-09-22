#define F_CPU 4915200

#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include <adc.h>
#include <uart.h>
#include <string.h>

#define ADC_ADDRESS 0x1400

void adc_test(void)
{
    uart_init(9600);
    adc_init();
    unsigned char data[4] = {0};

    while (1)
    {
        adc_read(data);
        
        // printf("%x\r\n", data[0] & 0xff);

        // 0,1: Joystick
        // 2, 3: L, R
        printf("Joystick: %x %x\r\n", data[0], data[1]);
        printf("Left PWM: %x\r\n", data[2]);
        printf("Right PWM: %x\r\n\n", data[3]);
        free(data);
        _delay_ms(200);
    }
    
}