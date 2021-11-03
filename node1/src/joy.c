#include <joy.h>
#include <can_bus.h>

/**
 * @brief Read analog position from joystick in percentage
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_analog(unsigned char *data, joy_t *joy)
{
    // [x/y]/middle * 100%: Percent from middle position
    joy->x_pos = (unsigned char)((data[1] * 100) / 255);
    joy->y_pos = (unsigned char)((data[0] * 100) / 255);
}

/**
 * @brief Find directon of joystick
 * @brief (Assumes that you have run joy_analog)
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_dir(unsigned char *data, joy_t *joy)
{
    /* Check direction */
    if (joy->y_pos > (joy->middle[0] + 5))
    {
        joy->dir = UP;
    }
    else if (joy->y_pos < (joy->middle[0] - 5))
    {
        joy->dir = DOWN;
    }
    else if (joy->x_pos > (joy->middle[1] + 5))
    {
        joy->dir = RIGHT;
    }
    else if (joy->x_pos < (joy->middle[1] - 5))
    {
        joy->dir = LEFT;
    }
    else
    {
        joy->dir = NEUTRAL;
    }
}

/**
 * @brief Calibrate joystick
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_calibrate(unsigned char *data, joy_t *joy)
{
    /* Set middle position */
    joy->middle[0] = (data[1] * 100) / 255;
    joy->middle[1] = (data[0] * 100) / 255;
}

/**
 * @brief Send joystick data on CAN buffer 0
 * 
 * @param joy Target joystick struct
 */
void joy_send(joy_t *joy)
{
    /* Initial configuration */
    can_bus_init();
    can_struct msg = {1, 2, {joy->x_pos, joy->y_pos}};

    /* Transmit data */
    can_transmit(&msg, 1);
}