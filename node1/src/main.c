#ifndef F_CPU
#define F_CPU 4915200
#endif
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include <uart.h>
#include <oled.h>

#include <ext.h>
#include <adc.h>
#include <gui.h>
#include <joy.h>
#include <uart.h>
#include <spi.h>
#include <can_bus.h>
#include <buttons.h>

int main(void)
{
	/* Declare variables */
	unsigned char data[4] = {0};
    can_struct rx;
	joy_t joy;

	/* Initialize libraries */
	uart_init(9600);
	adc_init();
	oled_init();
	menu_build();
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

		/* Run state machine, send game state over CAN */
		joy.game = (char)gui_run(&joy);
        joy_send(&joy);
	}
}