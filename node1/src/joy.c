#include <adc.h>
#include <joy.h>

/**
 * @brief Read analog position from joystick
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_analog(char *data, joy_t *joy)
{
    joy->x_pos = (data[0]/127) * 100;
    joy->x_pos = (data[1]/127) * 100;
}

/**
 * @brief Find directon of joystick
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_dir(char *data, joy_t *joy)
{
    
}