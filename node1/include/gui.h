#ifndef GUI_H
#define GUI_H

#include <joy.h>

typedef enum {
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_5
} state_t;

/**
 * @brief Run GUI state machine
 * 
 * @param joy Target joystick structure
 * @return bool Game running?
 */
int gui_run(joy_t *joy);

/**
 * @brief Build OLED GUI menu
 */
void menu_build(void);

#endif