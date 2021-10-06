#if !defined(JOY_H)
#define JOY_H

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} dir_t;

typedef struct
{
    int middle[2];
    int x_pos; // % Analog positions
    int y_pos;
    dir_t dir;
} joy_t;

/**
 * @brief Read analog position from joystick in percentage
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_analog(char *data, joy_t *joy);

/**
 * @brief Find directon of joystick
 * @brief (Assumes that you have run joy_analog)
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_dir(char *data, joy_t *joy);

/**
 * @brief Calibrate joystick
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_calibrate(char *data, joy_t *joy);

#endif // JOY_H
