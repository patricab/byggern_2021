#ifndef ADC_H
#define ADC_H

/**
 * @brief Read from ADC
 * 
 * @param ret adc_t return struct
 */
void adc_read(unsigned char *data);

/**
 * @brief Initialize ADC
 * 
 */
void adc_init(void);

#endif
