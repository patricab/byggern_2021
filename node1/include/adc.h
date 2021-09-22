#ifndef ADC_H
#define ADC_H

/**
 * @brief Read from ADC
 * 
 * @return char* Array of channel data
 */
char *adc_read(void);

/**
 * @brief Initialize ADC
 * 
 */
void adc_init(void);

#endif
