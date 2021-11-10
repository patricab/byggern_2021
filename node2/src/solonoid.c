#include <stdio.h>
#include <stdarg.h>
#include "solonoid.h"
#include "sam.h"


void solonoid_setup(void){
    /* Disable pull-up on bit PC2(D0) */
    PIOC->PIO_PUDR |= PIO_PC8;
    /* Enable PIO controller on bit PC2(D0) */
    PIOC->PIO_PER |= PIO_PC8;
    /* Set output enable on PC2(D0) */
    PIOC->PIO_OER |= PIO_PC8;
}

void run_solonoid(bool in_state){

    if (in_state == 1){
        PIOC->PIO_CODR |= PIO_PC8;
    } else {
        PIOC->PIO_SODR |= PIO_PC8;
    }
}


