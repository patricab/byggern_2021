#include "buttons.h"
#include <avr/io.h>
#include <stdio.h>

void buttons_init() {
	DDRB &= ~(1 << JOY_BUT_PIN);
	DDRB &= ~(1 << LEFT_BUT_PIN);
	DDRB &= ~(1 << RIGHT_BUT_PIN);
}

int joy_but() {
	return (PINB & (1 << JOY_BUT_PIN));
}

int left_but() {
	return (PINB & (1 << LEFT_BUT_PIN));
}

int right_but() {
	return (PINB & (1 << RIGHT_BUT_PIN));
}