#include <joy.h>

/**
 * @brief Read analog position from joystick in percentage
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_analog(char *data, joy_t *joy)
{
    // [x/y]/middle * 100%: Percent from middle position
    joy->x_pos = (data[0]/joy->middle[0]) * 100;
    joy->x_pos = (data[1]/joy->middle[1]) * 100;
}

/**
 * @brief Find directon of joystick
 * @brief (Assumes that you have run joy_analog)
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_dir(char *data, joy_t *joy)
{
    /* Check x-direction */
    if (joy->x_pos > (joy->middle[0] + 5)) {
        joy->dir = RIGHT;
    } else if (joy->x_pos < joy->middle[0]) {
       joy->dir = LEFT; 
    }

    /* Check y-direction */
    if (joy->y_pos > joy->middle[1]) {
       joy->dir = UP; 
    } else if (joy->y_pos < (joy->middle[1] + 5)) {
       joy->dir = DOWN; 
    }
}

/**
 * @brief Calibrate joystick
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_calibrate(char *data, joy_t *joy) {
    /* Set middle position */
   joy->middle[0] = data[0]; 
   joy->middle[1] = data[1]; 
}