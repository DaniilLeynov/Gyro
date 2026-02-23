#include "entity.h"
#include "window_settings.h"
#include <math.h>
#include "ring.h"
#include <stdlib.h>
#include <time.h>
// Now used for test struct
#define ENABLE 1
int main(void) {
    srand(time(NULL));
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
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {

        #if 0
        if (IsKeyPressed(KEY_RIGHT))
            change_dir *= -1;
        character.pos.x = radius * cos(angle) + (float)new_cord_x;
        character.pos.y = radius * sin(angle) + (float)new_cord_y;
        angle = (angle + 0.05f*change_dir);
        #endif
        BeginDrawing();

        ClearBackground(RAYWHITE);

        draw_ring(ring);

        change_picked_segment_state(ring);
        // DrawCircle((float)new_cord_x, (float)new_cord_y, (float)radius + 20.0f, BLUE);
        // DrawCircle((float)new_cord_x, (float)new_cord_y, (float)radius - 20.0f, RAYWHITE);
        //DrawCircleV(character.pos, character.shape.radius, character.color);

        EndDrawing();
    }


    free_ring(&ring);
    CloseWindow();
    return 0;
}


