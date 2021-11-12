#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#define DIR PIO_PD10 // DIRECTION
#define SEL PIO_PD2 // SELECTION
#define EN PIO_PD9 // ENABLE
#define NOT_OE PIO_PD0 // NOT OUTPUT ENABLE
#define NOT_RST PIO_PD1 // NOT RESET

void motor_controller_init();
void motor_enable();
void motor_disable();
void motor_run(int joy_pos);
int16_t motor_encoder_read(void);


#endif