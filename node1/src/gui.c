#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

#include <gui.h>
#include <oled.h>
#include <uart.h>

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
 
static state_t state_3() {
    oled_clear_pointer();
    oled_goto_pos(4,0);
    oled_print8("*");
}
 
static state_t state_4(){
    oled_clear_pointer();
    oled_goto_pos(6,0);
    oled_print8("*");
}


 
static state_t (*state_functions[4])() = {
    state_1,
    state_2,
    state_3,
    state_4,
    
    
};
 
 
/**
 * @brief Run GUI state machine
 * 
 * @param state state_t State enum
 * @param joy Target joystick structure
 */
_Bool gui_run(joy_t *joy){
        
    /* Change state based on joystick direction */
    if (joy->dir == DOWN) { //only works in menu
        state++;
    } else if (joy->dir == UP) {
        state--;
    }
    if (joy->dir == RIGHT) { // Select shit
        if (state == STATE_1){
            game_gui_run();
            return 1;

            //start spill
            //fjern pointer
            
        } 
        else if(state == STATE_2){
            choice2_build();
        } 
        else if(state == STATE_3){
            choice1_build();
        }
    }
    if (joy->dir == LEFT) { // Select shit
        menu_build();
        return 0;
    }

       /* Loop state on boundary condition */
    if (state == STATE_4 + 1){
        state = STATE_1;
    }
    else if (state == STATE_1 - 1){
        state = STATE_4;
    }

    (*state_functions[state])(); // Run state

    _delay_ms(10);
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
    oled_print8("Valg 2");
    oled_goto_pos(4, 15);
    oled_print8("Valg 3");
    oled_goto_pos(6, 15);
    oled_print8("Valg 4");
}

void choice1_build(void){
    state = STATE_1;

    oled_reset();   
    oled_goto_pos(0, 15);
    oled_print8("Menu1 1");
    oled_goto_pos(2, 15);
    oled_print8("Menu1 2");
    oled_goto_pos(4, 15);
    oled_print8("Menu1 3");
    oled_goto_pos(6, 15);
    oled_print8("Menu1 4");
}
void choice2_build(void){
    state = STATE_1;

    oled_reset();
    oled_goto_pos(0, 15);
    oled_print8("Menu2 1");
    oled_goto_pos(2, 15);
    oled_print8("Menu2 2");
    oled_goto_pos(4, 15);
    oled_print8("Menu2 3");
    oled_goto_pos(6, 15);
    oled_print8("Menu2 4");
}

void game_gui_run(void){

    oled_reset();
    oled_goto_pos(0, 15);
    oled_print8("Game running");

}

