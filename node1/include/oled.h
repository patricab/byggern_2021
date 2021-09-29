#ifndef oled_H
#define oled_H


/**
 * @brief Oled init
 * 
 */

void oled_init(void);
void oled_write_data(char data);
void oled_goto_line(int line);
void oled_reset();
void oled_home();
void oled_goto_column(int column);
void oled_clear_line(int line);
void oled_goto_pos(int line, int column);
void oled_print(char*);



#endif