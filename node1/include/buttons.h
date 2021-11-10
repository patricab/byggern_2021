#define JOY_BUT_PIN PINB0
#define LEFT_BUT_PIN DDB1
#define RIGHT_BUT_PIN DDB2


/**
 * @brief Initialize
 */
void buttons_init();

/**
 * @brief Reads the value on Port B Pin 0.
 *
 * @return The value on Port B Pin 0.
 */
int joy_but();

/**
 * @brief Reads the value on Port B Pin 1.
 *
 * @return The value on Port B Pin 1.
 */
int left_but();

/**
 * @brief Reads the value on Port B Pin 2.
 *
 * @return The value on Port B Pin 2.
 */
int right_but();