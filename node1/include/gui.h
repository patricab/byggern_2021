#ifndef gui_H
#define gui_H

#include <joy.h>

typedef enum {
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
} state_t;

/**
 * @brief Run GUI state machine
 * 
 * @param state state_t State enum
 * @param joy Target joystick structure
 */
void gui_run(joy_t *joy);

/**
 * @brief Build OLED GUI menu
 */
void menu_build(void);

void game_gui_run(void);
void choice1_build(void);
void choice2_build(void);

#endif