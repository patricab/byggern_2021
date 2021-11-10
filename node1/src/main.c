/*
 * Test_program.c
 *
 * Created: 01.09.2021 10:22:56
 * Author : andre
 */ 

#ifndef F_CPU
#define F_CPU 4915200
#endif
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include <uart.h>
#include <sram.h>
#include <spi.h>
#include <adc.h>
#include <joy.h>
#include <can_bus.h>

#include <test.h>

int main(void)
{
	/* Declare variables */
	unsigned char data[4] = {0};
	volatile joy_t joy;
	
	/* Initialize libraries */
	// uart_init(9600);
    adc_init();
	can_bus_init(); // also initialize SPI

    /* Read ADC and calibrate joystick */
    adc_read(data);
    joy_analog(data, &joy);

    _delay_ms(10);
    joy_calibrate(data, &joy);

    while (1) 
    {
        // Read ADC and get joystick position/direction
        adc_read(data);
        joy_analog(data, &joy);
        joy_dir(data, &joy);

        joy_send(&joy);
	}
}