#define F_CPU 4915200

#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <math.h>

#include <adc.h>
#include <joy.h>
#include <uart.h>
#include <string.h>
#include <test.h>

unsigned char data[4] = {0};
joy_t joy;

void joy_test(void)
{
    uart_init(9600);
    adc_init();
    
    /* Read ADC and calibrate joystick */
    adc_read(data);
    joy_analog(data, &joy);
    
    _delay_ms(10);
    joy_calibrate(data, &joy);

    while (1)
    {
        // ADC
        adc_read(data);
        
        // Joystick
        joy_analog(data, &joy);
        joy_dir(data, &joy);

        // 0,1: Joystick
        // 2, 3: L, R
        // printf("%d %d\r\n", data[0], data[1]);
        // printf("Middle pos: %d %d\r\n", joy.middle[0], joy.middle[1]);
        printf("Joystick pos: %d %d\r\n", joy.x_pos, joy.y_pos);
        printf("Joystick dir: %u\r\n\n", joy.dir);
        printf("Left PWM: %x\r\n", data[2]);
        printf("Right PWM: %x\r\n\n", data[3]);
        _delay_ms(200);
    }
    
}