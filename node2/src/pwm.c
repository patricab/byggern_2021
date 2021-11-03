

#include <stdio.h>
#include <stdarg.h>
#include "pwm.h"
#include "sam.h"



void pwm_init(void){

    //PMC->PMC_PCER1 |= (1 << 4);
    //REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM 

    REG_PMC_PCER1 |= (1 << 4);
    REG_PIOC_ABSR |= PIO_ABSR_P19;                        // Set PWM pin perhipheral type A or B, in this case B
    REG_PIOC_PDR |= PIO_PDR_P19;                          // Set PWM pin to an output
    REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);     // Set the PWM clock rate to 2MHz (84MHz/42) 
    REG_PWM_CMR0 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;      // Enable dual slope PWM and set the clock source as CLKA
    REG_PWM_CPRD0 = 20000;                                // Set the PWM frequency 2MHz/(2 * 20000) = 50Hz 
    REG_PWM_CDTY0 = 1500;                                 // Set the PWM duty cycle to 1500 - centre the servo
    REG_PWM_ENA = PWM_ENA_CHID5;                          // Enable the PWM channel     
    //REG_PWM_WPCR = PWM_WPCR_WPKEY(5265229);  //dec values
    REG_PWM_WPCR = PWM_WPCR_WPKEY(0x50574D);
    REG_PWM_WPCR |= PWM_WPCR_WPRG0 | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPCMD(0); 
    
    
}

void pwm_run(int joystic){
    



    REG_PWM_CDTY0 = 1500;  

}


// Enable clock
// Chose if ab or b
// Disable PIO

// PWM_CLK prescaler and divider 2MHz
// CMRn dual slope and clock source