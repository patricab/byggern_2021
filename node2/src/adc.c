#include <stdio.h>
#include <stdarg.h>

#include <adc.h>
#include "sam.h"

/**
 * @brief Initialize ADC library
 * 
 * @return True(0) or Error(1)
 */
int adc_init(void) {
    /* Setup for ADC mode register */
    REG_ADC_MR &= ~ADC_MR_TRGEN; // Disable hardware triggers
    REG_ADC_MR |= ADC_MR_LOWRES_BITS_12; // Set 12-bit resolution
    REG_ADC_MR |= ADC_MR_SLEEP_NORMAL; // Set ADC to normal mode
    REG_ADC_MR |= ADC_MR_FWUP_OFF; // Set normal sleep mode
    REG_ADC_MR |= ADC_MR_FREERUN_ON; // Enable Free Run Mode
    REG_ADC_MR |= ADC_MR_PRESCAL(41); // Set prescaler to 41 => 1MHz ADC clock
    REG_ADC_MR |= ADC_MR_STARTUP_SUT8; // Set startup time to 8 periods
    REG_ADC_MR |= ADC_MR_ANACH_NONE; // Turn off Analog Change
    REG_ADC_MR |= ADC_MR_TRACKTIM(4); // Set tracking time
    REG_ADC_MR |= ADC_MR_TRANSFER(1); // Set transfer period
    REG_ADC_MR |= ADC_MR_USEQ_NUM_ORDER; // Set Use sequence to normal mode

    /* Enable channel 0. Check if enabled */
    REG_ADC_CHER |= (1 << 0);
    if (!(REG_ADC_CHSR & (1 << 0))) {
        return 1;
    }

    return 0;
}

/**
 * @brief Read ADC data
 * 
 * @return unsigned char Last converted data
 */
unsigned char adc_read(void) {
   /* Start conversion */ 
   REG_ADC_CR |= (1 << ADC_CR_START);

   /* Wait until CH0 conversion is finished */
   while (!(REG_ADC_ISR & (1 << ADC_ISR_EOC0)))
   {
       /* Return last converted data */
       return (REG_ADC_LCDR & 0x7FF);
   }
}

/**
 * @brief Check if IR is blocked
 * 
 * @param data Data from ADC
 * @return true IR blocked
 * @return false IR not blocked
 */
bool ir_on(unsigned char *data) {
   return false; 
}