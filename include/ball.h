#ifndef BALL
#define BALL

#include "raylib.h"

typedef struct Ball Ball;

Ball *init_ball();

int draw_ball(Ball const* ball);
//must be contained in update
int rotate_ball(Ball *ball, int dir);

Vector2 get_ball_pos(Ball const *ball);

float get_ball_radius(Ball const *ball);

void free_ball(Ball **ball);

#endif
