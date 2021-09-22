#ifndef SRAM_H
#define SRAM_H

#include <stdint.h>

/**
 * @brief Write to SRAM address
 * 
 * @param address Address in SRAM
 * @param data Data to be sent
 * @return 0 if successful, 1 if errors occured
 */
int sram_write(uint16_t address, char data);

/**
 * @brief Read from SRAM address
 * 
 * @param address Address in SRAM
 * @return char 
 */
char sram_read(uint16_t address);

/**
 * @brief Initialize SRAM
 * 
 */
void sram_init(void);

#endif