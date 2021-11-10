#ifndef PWM_H
#define PWM_H

/**
 * @brief initialize pwm and moves the servo to the middle
 * 
 */
void pwm_init(void);

/**
 * @brief Set the pwm with so the servo can move. 
 * 
 * @param joy, the input must be between 0 and 255, if not the servo is set to middle value 
 */
void pwm_run(int joy);

#endif 