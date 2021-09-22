
#include <avr/io.h>

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
    TCCR1B =  (1 << CS10);

    //Timer setup 
    //Prescaler to 8
    //set interrupt
    //set bit i timsk register
    
    //disable interrupt
    //cli();

    //TIFR = (1 << OCF0);
    //OCR0 = //output compare
    //TCCR0 = (1 << CS01)  | (1 << WGM01);
    
    //enable interrupt
    //sei();

    




}

//commands for timer0 interrupt
//ISR(TIMER0_COMP_vect) 
    //do action


