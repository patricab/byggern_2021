#ifndef JOY_H
#define JOY_H

/* Direction struct */
typedef enum {
    NEUTRAL, // 0
    UP,      // 1
    DOWN,    // 2
    LEFT,    // 3
    RIGHT    // 4
} dir_t;

/* Joystick struct */
typedef struct {
    int middle[2];
    unsigned char x_pos; // % Analog positions
    unsigned char y_pos;
    dir_t dir;
} joy_t;

/**
 * @brief Read analog position from joystick in percentage
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_analog(unsigned char *data, joy_t *joy);

/**
 * @brief Find directon of joystick
 * @brief (Assumes that you have run joy_analog)
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_dir(unsigned char *data, joy_t *joy);

/**
 * @brief Calibrate joystick
 * 
 * @param data Array with data from ADC
 * @param joy Target joystick struct
 */
void joy_calibrate(unsigned char *data, joy_t *joy);

/**
 * @brief Send joystick data on CAN buffer 0
 * 
 * @param joy Target joystick struct
 */
void joy_send(joy_t *joy);

#endif // JOY_H
