#define F_CPU 4915200
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <adc_test.h>
#include <uart.h>
#include <ext.h>
#include <sram.h>
#include <spi.h>
#include <can_controller.h>
#include <can_bus.h>
#include <buttons.h>

int main(void)
{
	// ext_init();
	// sram_init();
	uart_init(9600);
	buttons_init();
	printf("NEW UPLOAD\n\r");

	while (1) {
		int joy_but_pos = joy_but();
		printf("%i\n\r", joy_but_pos);
		_delay_ms(50);
	}
}