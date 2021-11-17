#ifndef ADC_H
#define ADC_H

#include "sam.h"

/**
 * @brief Initialize ADC library
 * 
 * @return True(0) or Error(1)
 */
int adc_init(void);

/**
 * @brief Read ADC data
 * 
 * @return unsigned char Last converted data
 */
unsigned char adc_read(void);

/**
 * @brief Check if IR is blocked
 * 
 * @param data Data from ADC
 * @return true IR blocked
 * @return false IR not blocked
 */
bool ir_on(unsigned char *data);

#endif