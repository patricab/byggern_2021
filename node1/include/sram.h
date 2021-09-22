#ifdef SRAM_H
#define SRAM_H

#include <stdint.h>

/**
 * @brief Write to SRAM adress
 * 
 * @param adress Adress in SRAM
 * @param data Data to be sent
 * @return 0 if successful, 1 if errors occured
 */
int sram_write(uint16_t adress, char data);

/**
 * @brief Read from SRAM adress
 * 
 * @param adress Adress in SRAM
 * @return char 
 */
char sram_read(uint16_t adress);

/**
 * @brief Initialize SRAM
 * 
 */
void sram_init(void);

#endif