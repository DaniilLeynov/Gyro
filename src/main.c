#include "entity.h"
#include "window_settings.h"
#include <math.h>
#include "ring.h"
#include <stdlib.h>
#include <time.h>
#include "ball.h"
// Now used for test struct
#define ENABLE 1
int main(void) {
    srand(time(NULL));
    int dir = -1;
#if 0
    const int new_cord_x = SCREEN_WIDTH / 2;
    const int new_cord_y = SCREEN_HEIGHT / 2;
    const float radius = 40.0f;
    float angle = 0.0f;
    int change_dir = 1;
#endif
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
#if 0
    Entity character = {
        .shape = {
            .radius = 10.0f,
        },
        .color = MAROON,
        .velocity = 0.05f,
        .pos = { (float)new_cord_x, (float)new_cord_y}
    };
#endif

    Ring *ring = init_ring();
    add_segment_to_ring(&ring);

    Ball *ball = init_ball();


    SetTargetFPS(FPS);



    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_RIGHT))
            dir *= -1;
#if 0
        character.pos.x = radius * cos(angle) + (float)new_cord_x;
        character.pos.y = radius * sin(angle) + (float)new_cord_y;
        angle = (angle + 0.05f*change_dir);
#endif


        rotate_ball(ball, dir);
        BeginDrawing();

        ClearBackground(RAYWHITE);

        draw_ring(ring);
        draw_ball(ball);
        change_picked_segment_state(ring);
        // DrawCircle((float)new_cord_x, (float)new_cord_y, (float)radius + 20.0f, BLUE);
        // DrawCircle((float)new_cord_x, (float)new_cord_y, (float)radius - 20.0f, RAYWHITE);
        //DrawCircleV(character.pos, character.shape.radius, character.color);

        EndDrawing();
    }


    free_ring(&ring);
    free_ball(&ball);
    CloseWindow();
    return 0;
}


