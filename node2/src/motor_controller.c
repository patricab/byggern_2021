#include <stdio.h>
#include <stdarg.h>
#include "motor_controller.h"
#include "sam.h"
#include "dac.h"

void motor_controller_init() {
    /* Disable pull-up */
    //PIOD->PIO_PUDR |= EN;
 
    /* Enable PIO controller */
    PIOD->PIO_PER |= (EN | DIR | SEL | NOT_OE | NOT_RST);
    PIOC->PIO_PER |= (PIO_PER_P1 | PIO_PER_P2 | PIO_PER_P3 | PIO_PER_P4 | PIO_PER_P5 | PIO_PER_P6 | PIO_PER_P7 | PIO_PER_P8);
    /* Enable clock */
    PMC->PMC_PCER0 |= (1 << 13);
    /* Set input enabl for MJ2*/
    PIOC->PIO_ODR |= (PIO_ODR_P1 | PIO_ODR_P2 | PIO_ODR_P3 | PIO_ODR_P4 | PIO_ODR_P5 | PIO_ODR_P6 | PIO_ODR_P7 | PIO_ODR_P8);
    /* Set output enabl for MJ1*/
    PIOD->PIO_OER |= (EN | DIR | SEL | NOT_OE | NOT_RST);
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
    uint16_t u;
    if ((joy_pos >= 0) && (joy_pos <= 49)){
      PIOD->PIO_CODR |= DIR;
      u = joy_pos*40;
    }
    else if ((joy_pos >= 51) && (joy_pos <= 100)){
      PIOD->PIO_SODR |= DIR;
      u = joy_pos*40;
    }
    dac_conversion(u);
}

int16_t motor_encoder_read(void) {
    PIOD->PIO_CODR |= NOT_OE; // enable output from encoder
    PIOD->PIO_CODR |= SEL; // prep for get HIGH byte
    
    for (int i = 0; i < 2000; i++); // wait
    int8_t MSB = PIOC->PIO_PDSR; // get MSB

    PIOD->PIO_SODR |= SEL; // prep for get LOW byte
    for (int i = 0; i < 2000; i++); // wait
    int8_t LSB = PIOC->PIO_PDSR; // get LSB

    PIOD->PIO_SODR |= NOT_OE; // disable output from encoder
    int16_t encoder_value = (((uint16_t)(MSB << 8)) | LSB);
    return encoder_value;
}

void motor_encoder_reset(void) {
    PIOD->PIO_CODR |= NOT_RST;
    for (int i = 0; i < 2000; i++); // wait
    PIOD->PIO_SODR |= NOT_RST;
}