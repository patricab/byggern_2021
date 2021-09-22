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

/**
 * @brief Read from ADC
 * 
 * @return char* Array of channel data
 */
char *adc_read(void) {
    char data[4] = {0};

    ext_write(ADC_ADDRESS, 0x00, 0x00); // _WR strobe. Starts ADC sample and conversion
    _delay_ms(60); // Wait for conversion time
    for (int i = 0; i < 4; i++)
    {
       data[i] = ext_read(ADC_ADDRESS, 0x00); // _RD strobe. Read ADC channel in sequence
    }
    
    return data;
}

/**
 * @brief Initialize ADC
 * 
 */
void adc_init(void)
{
    ext_init();

    // PWM clock setup
    DDRD = (1 << PD5); //set PD5 as output
    OCR1A = 0x01FF; //Set duty cycle to 50% 
    
    // Set compare output mode and 10 bit fast PWM
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B =  (1 << CS10); // Set prescaling to 1

    // ADC setup
    set_bit(DDRB, DDB6); // Set _WR and _RD bits
    set_bit(DDRB, DDB7);
    set_bit(PORTB, PB6);
    set_bit(PORTB, PB7);
}