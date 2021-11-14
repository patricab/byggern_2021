#define F_CPU 4915200
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

// #include <uart.h>
// #include <bit.h>
#include <oled.h>

// #include <ext.h>
// #include <adc.h>
// #include <string.h>
#include <gui.h>
// #include <joy.h>

unsigned char d[4] = {0};
joy_t joy;

int main(void)
{
	/* Init functions */
	// ext_init();
	// adc_init();
	oled_init();
	// uart_init(9600);
	// oled_reset();
	// menu_build();
	
	/* Calibrate joystick and find initial direction */
	// adc_read(d);
    // joy_analog(d, &joy);
    // joy_calibrate(d, &joy);
	// joy_dir(d, &joy);

	while (1)
	{
		/* Get joystick direction */
		// adc_read(d);
		// joy_analog(d, &joy);
		// joy_dir(d, &joy);

		/* Run state machine */
		gui_run(&joy);
	}
	// oled_print8("SEND NUDES");
	// oled_goto_pos(1,0);
	// oled_print8("Oled");
}
