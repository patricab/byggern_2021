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
int game_state;
state_t state;
int score;

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
    game_state = 1;
    oled_clear_pointer();
    oled_reset();
    oled_goto_pos(0, 15);
    oled_print8("Game running");
    oled_goto_pos(4, 15);
    oled_print8(score);
}

static state_t (*state_functions[3])() = {
    state_1,
    state_2,
    state_3
};
 
/**
 * @brief Run GUI state machine
 * 
 * @param state state_t State enum
 * @param joy Target joystick structure
 */
int gui_run(joy_t *joy, int game_score){
    score = game_score;
    
    /* Change state based on joystick direction */
    if (joy->dir == DOWN) { // Only works in menu
        state++;
    } else if (joy->dir == UP) {
        state--;
    }
    
    /* Build menu based on state */
    if (joy->dir == RIGHT) { 
        if (state == STATE_1){ // Run game
            state = STATE_3;
        } else if (state == STATE_2){
            ui_score();
            game_state = 0;
        } 
    } else if (joy->dir == LEFT) { 
        menu_build();
        game_state = 0;
    }

    /* Loop state on boundary condition */
    if (state == STATE_3 + 1){
        state = STATE_1;
    }
    else if (state == STATE_1 - 1){
        state = STATE_3;
    }

    (*state_functions[state])(); // Run state

    _delay_ms(200);
    
    return game_state;
}

/**
 * @brief Build OLED GUI menu
 */
void menu_build(void)
{
    // Start in state 1
    state = STATE_1; 

    oled_reset();
    /* Build standard menu */
    oled_goto_pos(0, 15);
    oled_print8("Start spill");
    oled_goto_pos(2, 15);
    oled_print8("Scoreboard");
}

void ui_score(void){
    oled_clear_pointer();
    oled_reset();
    oled_goto_pos(0, 15);
    oled_print8(score);

    // oled_reset();   
    // oled_goto_pos(0, 15);
    // oled_print8("Menu1 1");
    // oled_goto_pos(2, 15);
    // oled_print8("Menu1 2");
    // oled_goto_pos(4, 15);
    // oled_print8("Menu1 3");
    // oled_goto_pos(6, 15);
    // oled_print8("Menu1 4");
}