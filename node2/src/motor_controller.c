#include <stdio.h>
#include <stdarg.h>
#include "motor_controller.h"
#include "sam.h"
#include "dac.h"
#include "uart.h"

// PID constants
int16_t Kp = 1;
int16_t Ti = 1;
int16_t Td = 1;
int16_t N = 10;
int16_t T = 0.01; // Time between runs
int16_t alpha = T / Ti;
int16_t beta = Td / (Td+T*N);

// Keep track of measurements
volatile int16_t ref = 0;
volatile int16_t rot[2] = {0, 0}; // rot[k], rot[k-1]
volatile int16_t error[2] = {0, 0}; // error[k], error[k-1]
// Keep track of u
volatile int16_t uP = 0;
volatile int16_t uI[2] = {0, 0};
volatile int16_t uD[2] = {0, 0};


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

void motor_controller_open_loop(int joy_pos) {
    int16_t u;
    int left_threshold = 40;
    int rigth_threshold = 60;
    if ((joy_pos >= 0) && (joy_pos <= left_threshold)){
      PIOD->PIO_CODR |= DIR; // Set direction
      u = (left_threshold-joy_pos)*(4000/left_threshold); // Scale
    }
    else if ((joy_pos >= rigth_threshold) && (joy_pos <= 100)){
      PIOD->PIO_SODR |= DIR; // Set direction
      u = (joy_pos-rigth_threshold)*((100-rigth_threshold)*100); // Scale
    }
    dac_conversion(u);
}

int16_t motor_encoder_read(void) {
    PIOD->PIO_CODR |= NOT_OE; // enable output from encoder
    PIOD->PIO_CODR |= SEL; // prep for get HIGH byte
    
    printf(" \n\r"); // wait
    uint8_t MSB = (PIOC->PIO_PDSR>>1); // get MSB

    PIOD->PIO_SODR |= SEL; // prep for get LOW byte
    printf(" \n\r"); // wait
    uint8_t LSB = (PIOC->PIO_PDSR>>1); // get LSB

    PIOD->PIO_SODR |= NOT_OE; // disable output from encoder
    int16_t encoder_value = MSB << 8 | LSB;
    return encoder_value;
}

void motor_encoder_reset(void) {
    PIOD->PIO_CODR |= NOT_RST;
    printf(" \n\r"); // wait
    PIOD->PIO_SODR |= NOT_RST;
}

void pid_controller(void) { // INTERRUPT, AND REFERENCE
    // Read inputs, reference (ref) and position (pos)
    rot[0] = motor_encoder_read();
    // read ref

    // Compute error signal
    error[0] = ref - rot[0]; // Calibration is necessary prior

    // Compute controller gain (position gain)
    uP = Kp * error[0];
    uI[0] = uI[1] + (Kp*alpha*error[0]);
    uD[0] = beta + uD[1] - (Kp*(Td/T)*(1-beta)*(rot[0]-rot[1]));
    int16_t u = uP + uI[0] + uD[0];

    // SET MOTOR DIRECTION AND SEND U TO DAC

    // Update previous signals
    error[1] = error[0];
    rot[1] = rot[0];
    uI[1] = uI[0];
    uD[1] = uD[0];
}

void tc_setup() {

  PMC->PMC_PCER1 |= PMC_PCER1_PID35;  // TC8 power ON : Enable pheriferal clock

  //PIOD->PIO_PDR |= PIO_PDR_P7;                            // Set the pin to the peripheral
  //PIOD->PIO_ABSR |= PIO_PD7B_TIOA8;                       // Peripheral type B

  TC2->TC_CHANNEL[2].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4  // MCK/2 = 42 M Hz, clk on rising edge
                              | TC_CMR_WAVE               // Waveform mode
                              | TC_CMR_WAVSEL_UP_RC;       // UP mode with automatic trigger on RC Compare
  //  | TC_CMR_ACPA_CLEAR         // Clear TIOA2 on RA compare match
  //  | TC_CMR_ACPC_SET;          // Set TIOA2 on RC compare match


  TC2->TC_CHANNEL[2].TC_RC = 656;  //<*********************  Frequency = (Mck/2)/TC_RC  Hz


  TC2->TC_CHANNEL[2].TC_IER = TC_IER_CPCS;
  NVIC_EnableIRQ(TC8_IRQn);
  TC2->TC_CHANNEL[2].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN; // Software trigger TC2 counter and enable
}

void TC8_Handler() {

  static uint32_t Count;

  TC2->TC_CHANNEL[2].TC_SR;                               // Read and clear status register
  if (Count++ == 1000) {
    Count = 0;
    PIOA->PIO_ODSR ^= PIO_ODSR_P19;                      // Toggle LED every 1 Hz
  }
}