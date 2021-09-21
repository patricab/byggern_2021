
#include <avr/io.h>

void ADC_init(void)
{
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM00) | (1 << COM01) | (1 << CS00);




}