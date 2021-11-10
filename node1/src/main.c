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
#include <buttons.h>

#include <test.h>

int main(void)
{
	/* Declare variables */
	unsigned char data[4] = {0};
	volatile joy_t joy;
	
	/* Initialize libraries */
	uart_init(9600);
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

        printf("Joystick pos: %d %d\r\n", joy.x_pos, joy.y_pos);
        printf("Joystick dir: %u\r\n\n", joy.dir);
        printf("Left PWM: %x\r\n", data[2]);
        printf("Right PWM: %x\r\n\n", data[3]);
        _delay_ms(200);
	}

	// uart_init(9600);
	// printf("NEW UPLOAD\n\r");

	// while (1) {
	// 	int joy_but_pos = joy_but();
	// 	printf("%i\n\r", joy_but_pos);
	// 	_delay_ms(50);

}