#ifndef ADC_H
#define ADC_H

typedef enum {CH1, CH2, CH3, CH4} channel_t;

/**
 * @brief Read from ADC
 * 
 * @param channel ADC channel to read. See _channel_t_
 * @return char* Array of channel data
 */
char *adc_read(channel_t channel) {

/**
 * @brief Initialize ADC
 * 
 */
void adc_init(void);

#endif
