#include <can_bus.h>
#include <buttons.h>

#include <joy.h>

/**
 * @brief Read analog position from joystick in percentage, as well as button press
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_analog(unsigned char *data, joy_t *joy)
{
    // [x/y]/middle * 100%: Percent from middle position
    joy->x_pos = (unsigned char)((data[1] * 100) / 255);
    joy->y_pos = (unsigned char)((data[0] * 100) / 255);

    joy->button = joy_but();
    joy->rpwm = data[3];
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
    can_struct msg = {
        .id = 1, 
        .length = 5, 
        .data[0] = joy->x_pos, 
        .data[1] = joy->y_pos,
        .data[2] = joy->button,
        .data[3] = joy->rpwm,
        .data[4] = joy->game
    };

    /* Transmit data */
    can_transmit(&msg, 0);
}