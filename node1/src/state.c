#include <stdio.h>
#include <unistd.h>
#include <avr/io.h>
#include <util/delay.h>

#include <oled.h>



typedef enum {
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
} state_t;
 
static void state_1() {
    oled_clear_pionter();   
    oled_goto_pos(0,0);
    oled_print8("*");
    
}
 
static void state_2() {
    oled_clear_pionter();
    oled_goto_pos(2,0);
    oled_print8("*");
    
}
 
static void state_3() {
    oled_clear_pionter();
    oled_goto_pos(4,0);
    oled_print8("*");
    
    
}
 
static void state_4(){
    oled_clear_pionter();
    oled_goto_pos(6,0);
    oled_print8("*");


}
 
static void(*state_functions[4])() = {
    state_1,
    state_2,
    state_3,
    state_4,
};
 
void oled_run(void){
    // Start in state 1
    state_t state = STATE_1;
 
    // Run the finite state machine forever
    while(1){
        (*state_functions[state])();
         
        //if (//retning = ned )
        //state++;
        //else if (// retning = opp)
        //state--;

        
        if (state == STATE_4 + 1){
            state = 0;
        }
        else if (state == STATE_1 - 1){
            state = 4;
        }

        _delay_ms(1000);
         
         
        
    }
}

