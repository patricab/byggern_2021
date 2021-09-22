#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>

#include <sram.h>
#include <ext.h>

#define SRAM_ADDRESS 0x800

/**
 * @brief Write to SRAM address
 * 
 * @param address Address in SRAM
 * @param data Data to be sent
 * @return 0 if successful, 1 if errors occured
 */
int sram_write(uint16_t address, char data) {
    if (address > 0x7FF)
    {
        printf("SRAM address out of range\n");
        return 1;
    }

    ext_write(SRAM_ADDRESS, address, data);
    return 0;
}

/**
 * @brief Read from SRAM address
 * 
 * @param address Address in SRAM
 * @return char 
 */
char sram_read(uint16_t address) {
    if (address > 0x7FF)
    {
        printf("SRAM address out of range\n");
        return 1;
    }

    return ext_read(SRAM_ADDRESS, address);
}

/**
 * @brief Initialize SRAM
 * 
 */
void sram_init(void) {
	// Enable external SRAM
    MCUCR |= (1 << SRE);

	// Mask JTAG bits
    SFIOR &= ~(111 << XMM0);
    SFIOR |= (1 << XMM2);
}