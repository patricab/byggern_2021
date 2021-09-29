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
    int x_pos; // % Analog positions
    int y_pos;
    dir_t dir;
} joy_t;

#endif // JOY_H
