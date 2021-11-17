#include <stdio.h>
#include <stdarg.h>

#include "sam.h"
#include "uart.h"
#include <motor_controller.h>
#include <dac.h>
#include <pwm.h>
#include <printf-stdarg.h>
#include <can_controller.h>

void delay(int ms) {
   int i = 0;
   while (i < ms){i++;}
}

int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    /* Initialize libraries */
    configure_uart();
    pwm_init();
    motor_controller_init();
    motor_enable();
    dac_init();
    tc_setup();
    //motor_encoder_calib();

    //motor_encoder_reset();
    // // Function motor_encoder_reset() does not work
    PIOD->PIO_CODR |= NOT_RST;
    printf(" \n\r"); // wait
    PIOD->PIO_SODR |= NOT_RST;

    uint8_t ret = can_init_def_tx_rx_mb();
    if (ret > 0) {
        printf("Error: could not initialize CAN", 0);
    }

    /* Disable pull-up on bit PC2(D0) */
    PIOA->PIO_PUDR |= PIO_PA19;
    /* Enable PIO controller on bit PC2(D0) */
    PIOA->PIO_PER |= PIO_PA19;
    /* Set output enable on PC2(D0) */
    PIOA->PIO_OER |= PIO_PA19;
    
    CAN_MESSAGE msg;

    int i;
    REG_PIOA_OWER |= PIO_PA19;
    
    while (1)
    {

        can_receive(&msg, 0);
        // printf("ID : %d\r\nLength: %d\r\nData: %x %x\r\n\n", msg.id, msg.data_length, msg.data[0], msg.data[1]);
        // delay(1000000);
        update_ref((int16_t)msg.data[3]);
        pid_controller();
        //printf("%d\n\r", msg.data[3]);
        pwm_run((int)msg.data[0]);
        // int16_t value = motor_encoder_read();
        // printf("%d\n\r", value);
    }   
}