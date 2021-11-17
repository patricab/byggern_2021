#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#define DIR PIO_PD10 // DIRECTION
#define SEL PIO_PD2 // SELECTION
#define EN PIO_PD9 // ENABLE
#define NOT_OE PIO_PD0 // NOT OUTPUT ENABLE
#define NOT_RST PIO_PD1 // NOT RESET

extern volatile int16_t ref;

/**
 * @brief Initialize motor controller
 * 
 */
void motor_controller_init();

/**
 * @brief Enable motor on motorbox
 * 
 */
void motor_enable();

/**
 * @brief Disable motor on motorbox
 * 
 */
void motor_disable();

/**
 * @brief Controll motor with joystick pos and open loop
 * 
 * @param joy_pos Between 0 and 100. 50 is mid pos.
 */
void motor_controller_open_loop(int joy_pos);

/**
 * @brief Read encoder value
 * 
 * @return int16_t What is the value?
 */
int16_t motor_encoder_read(void);

/**
 * @brief Reset motor encoder
 * 
 */
void motor_encoder_reset(void);

/**
 * @brief Calibrate motro encoder
 * 
 */
void motor_encoder_calib(void);

/**
 * @brief Running with timer interrupt
 * 
 */
void pid_controller(void);

/**
 * @brief Has to run in main loop to update user reference
 * 
 * @param get_ref 
 */
void update_ref(int16_t get_ref);

/**
 * @brief Init of timer interrupt
 * 
 */
void tc_setup(void);


#endif