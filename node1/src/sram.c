#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sram.h>
#include <avr/io.h>

#define SRAM_ADRESS 0x800

/**
 * @brief Write to SRAM adress
 * 
 * @param adress Adress in SRAM
 * @param data Data to be sent
 * @return 0 if successful, 1 if errors occured
 */
int sram_write(uint16_t adress, char data) {
    if (adress > 0x7FF)
    {
        printf("SRAM adress out of range\n");
        return 1;
    }
    volatile char *ext_ram = SRAM_ADRESS;
    ext_ram[adress] = data;

    return 0;
}

/**
 * @brief Read from SRAM adress
 * 
 * @param adress Adress in SRAM
 * @return char 
 */
char sram_read(uint16_t adress) {
    if (adress > 0x7FF)
    {
        printf("SRAM adress out of range\n");
        return 1;
    }

    volatile char *ext_ram = SRAM_ADRESS;

    return ext_ram[adress];
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