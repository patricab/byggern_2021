#ifndef EXT_H
#define EXT_H

/**
 * @brief Write to external memory
 * 
 * @param mem_adress Memory adress i external RAM
 * @param adress Internal adress of memory partition
 * @param data Data to be written
 */
void ext_write(char* mem_adress, char adress, char data);

/**
 * @brief Read from external memory
 * 
 * @param mem_adress Memory adress i external RAM
 * @param adress Internal adress of memory partition
 * @return char Data to be read
 */
char ext_read(char* mem_adress, char adress);

/**
 * @brief Initialize external RAM
 * 
 */
void ext_init(void);

#endif