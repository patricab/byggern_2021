#include <stdio.h>
#include <stdarg.h>
#include "solonoid.h"
#include "sam.h"


void solonoid_setup(void){
    /* Disable pull-up on bit PC2(D0) */
    PIOC->PIO_PUDR |= PIO_PC9;
    /* Enable PIO controller on bit PC2(D0) */
    PIOC->PIO_PER |= PIO_PC9;
    /* Set output enable on PC2(D0) */
    PIOC->PIO_OER |= PIO_PC9;
}

void run_solonoid(_Bool in_state){

    if (in_state == 1){
        PIOC->PIO_CODR |= PIO_PC9;
    } else {
        PIOC->PIO_SODR |= PIO_PC9;
    }
}


