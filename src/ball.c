#include <stdlib.h>
#include <math.h>
#include "ball.h"
#include "window_settings.h"
#include "settings.h"

struct Ball {
    float radius;
    Color color;
    // pos contains polar cords {radius-vector relative to center of ring}
    Vector2 pos;
    bool shield;
    float velocity;
};

static Vector2 calculate_tarns_to_global_cords(float radius, float angle);

Ball *init_ball() {
    Ball *ball;
    ball = (Ball *)malloc(sizeof(Ball));
    if (ball == NULL) return NULL;

    *ball = (Ball) {
        .radius = (RING_BIG_RADIUS - RING_LITTLE_RADIUS) / 2 / BALL_RADIUS_SCALLER_FACTOR,
        .color = BALL_COLOR,
        .pos = {(float)(RING_LITTLE_RADIUS + (RING_BIG_RADIUS - RING_LITTLE_RADIUS) / 2),
                0.0f
               },
        .velocity = DEFAULT_BALL_VELOCITY,
        .shield= false,
    };

    return ball;
};

Vector2 get_ball_pos(Ball const *ball) {
    if (ball == NULL) return (Vector2) {
        0.0f, 0.0f
    };
    return ball->pos;
}

float get_ball_radius(Ball const *ball) {
    if (ball == NULL) return 0.0f;
    return ball->radius;
}

int draw_ball(Ball const *ball) {
    if (ball == NULL) return -1;
    DrawCircleV(calculate_tarns_to_global_cords(ball->pos.x, ball->pos.y),
                ball->radius,
                ball->color);
    return 0;
}

int rotate_ball(Ball *ball, int dir, float delta_time) {
    if (ball == NULL) return -1;
    ball->pos.y += ball->velocity * (float)dir * delta_time;
    return 0;
}

void free_ball(Ball **ball) {
    if (ball == NULL || *ball == NULL) return;
    free(*ball);
    ball = NULL;
}

static Vector2 calculate_tarns_to_global_cords(float radius, float angle) {
    Vector2 vec;
    vec.x = radius * cos(angle) + SCREEN_WIDTH / 2;
    vec.y = radius * sin(angle) + SCREEN_HEIGHT / 2;
    return vec;
}
