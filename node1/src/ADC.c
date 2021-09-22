
#include <avr/io.h>
#include <bit.h>

/**
 * @brief Initialize ADC
 * 
 */

void adc_init(void)
{
    //PWM setup
    //set PD5 as output
    DDRD = (1 << PD5);
    //Set duty cycle to 50%
    OCR1A = 0x01FF; 
    // Set compare output mode and 10 bit fast PWM
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    //set prescaling to 1

    set_bit(TCCR1B, CS10); //TCCR1B =  (1 << CS10);

    
}



