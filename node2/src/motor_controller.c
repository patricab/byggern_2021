#include <stdio.h>
#include <stdarg.h>
#include "motor_controller.h"
#include "sam.h"
#include "dac.h"

void motor_controller_init() {
    /* Disable pull-up */
    PIOD->PIO_PUDR |= EN;
    /* Enable PIO controller */
    PIOD->PIO_PER |= EN;
    /* Set output enabl */
    PIOD->PIO_OER |= EN;
}

void motor_enable() {
    // Set EN high
    PIOD->PIO_SODR |= EN;
}

void motor_disable() {
    // Set EN low
    PIOD->PIO_CODR |= EN;
}

void motor_run(int joy_pos) {
    if ((joy_pos >= 0) && (joy_pos <= 100)){
        int u = joy_pos*40;
        dac_conversion(u);
    }
}