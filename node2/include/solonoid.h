
#ifndef PWM_H
#define PWM_H

/**
 * @brief If input is high the solonoid is activated
 * 
 */
void run_solonoid(_Bool in_state);


/**
 * @brief setup the solonoid pin
 * 
 */
void solonoid_setup(void);



#endif 