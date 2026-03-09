#ifndef ENEMIES
#define ENEMIES

#include "raylib.h"

typedef enum Enemy_state Enemy_state;

typedef struct Enemy Enemy;

typedef struct Enemies Enemies;

// In the future, the structures should be hidden
enum Enemy_state {
    IDLE,
    MOVING,
};

struct Enemy {
    Vector2 size;
    Color color;
    Vector2 pos;
    float velocity;
    bool is_visible;
    Enemy_state state;
    int id;
};

struct Enemies {
    int num_of_enemies;
    Enemy **enemies;
};

Enemies *init_enemies();

int draw_enemies(Enemies const *enemies);

int update_enemies(Enemies *enemies, float delta_time);

const int get_num_of_enemies(Enemies const *enemy);

void free_enemies(Enemies **enemies);

#endif
