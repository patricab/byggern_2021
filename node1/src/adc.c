#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <bit.h>
#include <ext.h>
#include <adc.h>

#define ADC_ADDRESS 0x1400

volatile int x_off;
volatile int y_off;

/* Auto calibrate ADC */
static adc_calibrate(void) {
    ext_write(ADC_ADDRESS, 0x00, 0x00); // _WR strobe. Starts ADC sample and conversion
    _delay_ms(60); // Wait for conversion time
    x_off = ext_read(ADC_ADDRESS, 0x00) - 127; // _RD strobe. Find x offset value
    y_off = ext_read(ADC_ADDRESS, 0x00) - 127; // _RD strobe. Find y offset value
}

/**
 * @brief Read from ADC
 * 
 * @param ret adc_t return struct
 */
void adc_read(char *data) {
    // Channel 0,1: Joystick
    // Channel 2, 3: Left slider, Right slider

    ext_write(ADC_ADDRESS, 0x00, 0x00); // _WR strobe. Starts ADC sample and conversion
    _delay_ms(60); // Wait for conversion time
    for (int i = 0; i < 4; i++)
    {
        data[i] = ext_read(ADC_ADDRESS, 0x00); // _RD strobe. Read ADC channel in sequence
        if (i == 0)
        {
            int val = (int)data[i] - x_off;
            
            if (val < 0) { // Cut end regions off joystick range
                val = 0;
            } else if (val > 255)
            {
                val = 255;
            }

            data[i] = (char)val; // Set new data
        } else if (i == 1)
        {
            int val = (int)data[i] - y_off;

            if (val < 0) { // Cut end regions off joystick range
                val = 0;
            } else if (val > 255)
            {
                val = 255;
            }

            data[i] = (char)val;
        }
    }
}

/**
 * @brief Initialize ADC
 */
void adc_init(void)
{
    ext_init();
    adc_calibrate(); // Calibrate and find offset values

    // PWM clock setup
    DDRD = (1 << PD5); //set PD5 as output
    OCR1A = 0x01FF; //Set duty cycle to 50% 
    
    // Set compare output mode and 10 bit fast PWM
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B =  (1 << CS10); // Set prescaling to 1
}