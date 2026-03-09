#ifndef ENEMIES
#define ENEMIES

#include "raylib.h"

typedef enum Enemy_state {
    IDLE,
    MOVING,
} Enum_state;

typedef struct Enemy {
    Vector2 size;
    Color color;
    Vector2 pos;
    float velocity;
    bool is_visible;
    Enum_state state;
    int id;
} Enemy;

typedef struct Enemies {
    int num_of_enemies;
    Enemy **enemies;
} Enemies;


Enemies *init_enemies();

int draw_enemies(Enemies const *enemies);

int update_enemies(Enemies *enemies, float delta_time);

void free_enemies(Enemies **enemies);

#endif
