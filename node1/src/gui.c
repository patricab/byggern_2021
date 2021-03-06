#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

#include <gui.h>
#include <oled.h>

/* Variables */
int game_state = 0;
state_t state;

static state_t state_1() {
    oled_clear_pointer();   
    oled_goto_pos(0,0);
    oled_print8("*");
}
 
static state_t state_2() {
    oled_clear_pointer();
    oled_goto_pos(2,0);
    oled_print8("*");
}

static state_t state_3() { // Game running
}

static state_t state_4() { // Scoreboard
    game_state = 1;
    oled_clear_pointer();
    oled_reset();
    oled_goto_pos(0, 15);
    oled_print8("Game running");
}

static state_t state_5() { // Scoreboard
    game_state = 0;
    oled_clear_pointer();
    oled_reset();
    oled_goto_pos(0, 15);
    oled_print8("Score!");
}

static state_t (*state_functions[5])() = {
    state_1,
    state_2,
    state_3,
    state_4,
    state_5
};
 
/**
 * @brief Run GUI state machine
 * 
 * @param state state_t State enum
 * @param joy Target joystick structure
 */
int gui_run(joy_t *joy){
    /* Change state based on joystick direction */
    if ((state == STATE_4) || (state == STATE_5)) {
        if (joy->left_but == 2) {
            state = STATE_1;
            menu_build();
        } 
    } else {
        if (joy->dir == DOWN) { // Only works in menu
            state++;
        } else if (joy->dir == UP) {
            state--;
        }
    }
    
    /* Build menu based on state */
    if (joy->dir == RIGHT) { 
        if (state == STATE_1){ // Run game
            state = STATE_4;
        } else if (state == STATE_2){
            state = STATE_5;
        } 
    }

    /* Loop state on boundary condition */
    if (state == STATE_2 + 1){
        state = STATE_1;
    }
    else if (state == STATE_1 - 1){
        state = STATE_2;
    }

    (*state_functions[state])(); // Run state

    if (game_state == 0){
        _delay_ms(100);
    }

    return game_state;
}

/**
 * @brief Build OLED GUI menu
 */
void menu_build(void){
    // Start in state 1
    state = STATE_1; 
    game_state = 0;

    oled_reset();
    /* Build standard menu */
    oled_goto_pos(0, 15);
    oled_print8("Start spill");
    oled_goto_pos(2, 15);
    oled_print8("Scoreboard");
}