#include <avr/io.h>
#include <adc.h>
#include <ext.h>

#define ADC_ADDRESS 0x1400


/**
 * @brief Read from ADC
 * 
 * @param channel ADC channel to read. See _channel_t_
 * @return char* Array of channel data
 */
char *adc_read(channel_t channel) {
    char data[8] = {0};

    ext_write(ADC_ADDRESS, 0x00, 0x00); // _WR strobe. Starts ADC sample and conversion
    _delay_ms(60); // Wait for conversion time
    for (int i = 0; i <= channel; i++)
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
    // PWM clock setup
    DDRD = (1 << PD5); //set PD5 as output
    OCR1A = 0x01FF; //Set duty cycle to 50% 
    
    // Set compare output mode and 10 bit fast PWM
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B =  (1 << CS10); // Set prescaling to 1

    // ADC setup
    DDRB |= (1 << DDB6) | (1 << DDB7); // Set _WR and _RD bits
    PORTB |= (1 << PB7) | (1 << PB6); 
    


}