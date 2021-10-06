#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

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
void gui_run(joy_t *joy){
        
    /* Change state based on joystick direction */
    if (joy->dir == DOWN) {
        state++;
    } else if (joy->dir == UP) {
        state--;
    }
    if (joy->dir == RIGHT) { // Select shit
        oled_reset();
        oled_goto_pos(0, 12);
        oled_print8("Send nudes");
    }

    /* Loop state on boundary condition */
    if (state == STATE_4 + 1){
        state = STATE_1;
    }
    else if (state == STATE_1 - 1){
        state = STATE_4;
    }

    (*state_functions[state])(); // Run state

    _delay_ms(100);
}

/**
 * @brief Build OLED GUI menu
 */
void gui_build(void)
{
    // Start in state 1
    state = STATE_1; 

    /* Build standard menu */
    oled_goto_pos(0, 15);
    oled_print8("Valg 1");
    oled_goto_pos(2, 15);
    oled_print8("Valg 2");
    oled_goto_pos(4, 15);
    oled_print8("Valg 3");
    oled_goto_pos(6, 15);
    oled_print8("Valg 4");
}