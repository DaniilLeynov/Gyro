#include "entity.h"
#include "stdio.h"
#include "window_settings.h"
#include <math.h>
#include "ring.h"
#include <stdlib.h>
#include <time.h>
#include "ball.h"
#include "enemies.h"

Vector2 calculate_tarns_to_global_cords_t(float radius, float angle) {
    Vector2 vec;
    vec.x = radius * cos(angle) + SCREEN_WIDTH / 2;
    vec.y = radius * sin(angle) + SCREEN_HEIGHT / 2;
    return vec;
}


// Now used for test struct
#define ENABLE 1
int main(void) {
    int count_of_collisin = 0;
    Color bg_color = RAYWHITE;
    float delta_time;
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

    Enemies *enemies = init_enemies();


    SetTargetFPS(FPS);



    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_RIGHT))
            dir *= -1;
#if 0
        character.pos.x = radius * cos(angle) + (float)new_cord_x;
        character.pos.y = radius * sin(angle) + (float)new_cord_y;
        angle = (angle + 0.05f*change_dir);
#endif
        bg_color = RAYWHITE;
        delta_time = GetFrameTime();
        update_enemies(enemies, delta_time);
        rotate_ball(ball, dir);
        for (int i = 0; i < enemies->num_of_enemies; i++) {
            Rectangle rect = { enemies->enemies[i]->pos.x, enemies->enemies[i]->pos.y, enemies->enemies[i]->size.x, enemies->enemies[i]->size.y };
            if (CheckCollisionCircleRec(calculate_tarns_to_global_cords_t(ball->pos.x, ball->pos.y), ball->radius, rect)) {
                printf("collision %d id=%d \n", count_of_collisin++, enemies->enemies[i]->id);
                bg_color = RED;
            }
        }
        BeginDrawing();

        ClearBackground(bg_color);

        draw_ring(ring);
        draw_ball(ball);
        draw_enemies(enemies);
        //change_picked_segment_state(ring);
        // DrawCircle((float)new_cord_x, (float)new_cord_y, (float)radius + 20.0f, BLUE);
        // DrawCircle((float)new_cord_x, (float)new_cord_y, (float)radius - 20.0f, RAYWHITE);
        //DrawCircleV(character.pos, character.shape.radius, character.color);

        EndDrawing();
    }

    free_enemies(&enemies);
    free_ring(&ring);
    free_ball(&ball);
    CloseWindow();
    return 0;
}


