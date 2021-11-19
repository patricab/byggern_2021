#ifndef oled_H
#define oled_H

/**
 * @brief Initialize OLED
 */

void oled_init(void);

/**
 * @brief Write to data section of OLED memory
 * 
 * @param data Data to be written
 */
void oled_write_data(char data);

/**
 * @brief Set line to start writing from
 * 
 * @param line Line position
 */
void oled_goto_line(int line);

/**
 * @brief Turns all pixels off
 * 
 */
void oled_reset(void);

/**
 * @brief Set writing position to (0,0)
 * 
 */
void oled_home(void);

/**
 * @brief Set column to write on
 * 
 * @param column Column position
 */
void oled_goto_column(int column);

/**
 * @brief Set line to write on
 * 
 * @param line Line position
 */
void oled_clear_line(int line);

/**
 * @brief Clear the pointer in OLED menu
 * 
 */
void oled_clear_pointer(void);

/**
 * @brief Set position to write on
 * 
 * @param line Line position
 * @param column Column position
 */
void oled_goto_pos(int line, int column);

/**
 * @brief Print 8-bit wide string on OLED
 * 
 * @param string String to print
 */
void oled_print8(char* string);

#endif