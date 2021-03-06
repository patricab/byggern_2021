#include <stdio.h>
#include <stdarg.h>
#include "pwm.h"
#include "sam.h"


/**
 * @brief initialize pwm and moves the servo to the middle
 * 
 */

void pwm_init(void){

    REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);     // Set the PWM clock rate to 2MHz (84MHz/42) 
    PMC->PMC_PCER1 |= (1 << 4);                           // Enable PWM 
    REG_PIOC_PDR |= PIO_PDR_P19;                          // Set PWM pin to an output
    REG_PIOC_ABSR |= PIO_ABSR_P19;                        // Set PWM pin perhipheral type A or B, in this case B
    REG_PWM_WPCR = PWM_WPCR_WPKEY(0x50574D);              // Set protection key 
    REG_PWM_WPCR |= PWM_WPCR_WPRG0 | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPCMD(0); //enable write protection 
    REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;      // Enable dual slope PWM and set the clock source as CLKA
    REG_PWM_CPRD5 = 20000;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz 
    REG_PWM_ENA = PWM_ENA_CHID5;                          // Enable the PWM channel     
    REG_PWM_CDTY5 = 18500;                                 // Set the PWM duty cycle to 1500 - centre the servo
}

/**
 * @brief Set the pwm with so the servo can move. 
 * 
 * @param joy, the input must be between 0 and 255, if not the servo is set to middle value 
 */

void pwm_run(int joystic){
    
    if ((joystic >= 0) && (joystic <=100)) {
        REG_PWM_CDTY5 = (20000-(900 + (1200-(joystic*12))));
    }   else {
        REG_PWM_CDTY5 = (20000-1500); 
    }
}

