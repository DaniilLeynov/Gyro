#ifndef BALL
#define BALL

#include "raylib.h"

typedef struct Ball {
    float radius;
    Color color;
    // pos contains polar cords {radius-vector relative to center of ring}
    Vector2 pos;
    bool shield;
    float velocity;
} Ball;

Ball *init_ball();

int draw_ball(Ball const* ball);

int rotate_ball(Ball *ball, int dir);

void free_ball(Ball **ball);

#endif
