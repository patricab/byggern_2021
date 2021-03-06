#include <stdio.h>
#include <stdarg.h>

#include <adc.h>
#include "sam.h"

// Forward declaration
unsigned char IR_average_filter(void);

/**
 * @brief Initialize ADC library
 * 
 * @return True(0) or Error(1)
 */
int adc_init(void) {
    /* Setup for ADC mode register */
    REG_PMC_PCER1 |= PMC_PCER1_PID37; // enable clock for ADC
    REG_ADC_MR |= ADC_MR_FREERUN;
    REG_ADC_CHER |= ADC_CHER_CH0; // enable adc for channel 0 (A7?)
    return 0;
}

/**
 * @brief Read ADC data
 * 
 * @return unsigned char Last converted data
 */
unsigned char adc_read(void) {
    REG_ADC_CR |= ADC_CR_START; // start conversion
    
    while(!(REG_ADC_ISR));
    return ADC->ADC_CDR[0];
}

/**
 * @brief Check if IR is blocked
 * 
 * @param data Data from ADC
 * @return true IR blocked
 * @return false IR not blocked
 */
int ir_on(void) {
    /* Get average IR values */
    unsigned char data = adc_read();
    
    if(data < 30){
        return 1;
    }
    else {
        return 0;
    }
}

#define num_readings 5
volatile unsigned char array[num_readings];
volatile uint8_t index = 0;
volatile  unsigned char total = 0;

unsigned char IR_average_filter(void) {
	total = total - array[index];
	array[index] = adc_read();
	total = total + array[index];
	index = index + 1;
	if (index >= num_readings) {
		index = 0;
	}
	unsigned char average = total / num_readings;
	return average;
}