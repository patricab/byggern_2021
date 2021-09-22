#include <stdlib.h>
#include <ext.h>
#include <sram.h>

/**
 * @brief Write to external memory
 * 
 * @param mem_adress Memory adress in external RAM
 * @param adress Internal adress of memory partition
 * @param data Data to be written
 */
void ext_write(char mem_adress, char adress, char data) {

    volatile char *ext = mem_adress; // Set adress pointer
    ext[adress] = data;

}

/**
 * @brief Read from external memory
 * 
 * @param mem_adress Memory adress in external RAM
 * @param adress Internal adress of memory partition
 * @return char Data to be read
 */
char ext_read(char mem_adress, char adress) {

    volatile char *ext = mem_adress; // Set adress pointer
    return ext[adress];

}

/**
 * @brief Initialize external RAM
 * 
 */
void ext_init(void) {sram_init();}