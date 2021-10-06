/*
 * Test_program.c
 *
 * Created: 01.09.2021 10:22:56
 * Author : andre
 */ 

#define F_CPU 4915200
#define __AVR_ATmega162__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include <test.h>
#include <uart.h>
#include <bit.h>
#include <oled.h>
#include <ext.h>
#include <string.h>
#include <gui.h>

<<<<<<< HEAD
=======
int main(void)
{
	// adc_test();	
	joy_test();

	// ext_init();
>>>>>>> joy


int main(void)
{
	ext_init();
	oled_init();
	uart_init(9600);
	
	oled_reset();
	oled_print8("SEND NUDES");
	oled_goto_pos(1,0);
	oled_print8("Oled");
}
