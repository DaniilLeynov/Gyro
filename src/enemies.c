#include <stdlib.h>
#include "enemies.h"
#include "settings.h"
#include "window_settings.h"
#include "stdio.h"


static Enemy *init_enemy();
static int draw_enemy(Enemy const *enemy);
static int setup_move_enemy(Enemy *enemy);
static int setup_idle_enemy(Enemy *enemy);
static bool is_enemy_out_of_bound(Enemy const *enemy);
static int move_enemy(Enemy *enemy);
static void free_enemy(Enemy **enemy);

static Vector2 calculate_enemy_start_pos(Vector2 enemy_size) {
    float x, y;
    Vector2 vec;
    //fixme
    x = -enemy_size.x; //always in -enemy width
    y = (float)(rand() % (SCREEN_HEIGHT - (int)enemy_size.y));
    vec = (Vector2) {
        x, y
    };

    return vec;
}

static float calculate_enemy_velocity() {
    float velocity;
    float random_factor = (float)rand() / (float)RAND_MAX;
    velocity = ENEMY_MIN_VELOCITY +
               random_factor * (ENMEY_MAX_VELOCITY - ENEMY_MIN_VELOCITY);
    return velocity;
}

static Enemy *init_enemy(int id) {
    Enemy *enemy;
    enemy = (Enemy *)malloc(sizeof(Enemy));
    if (enemy == NULL) return NULL;

    *enemy = (Enemy) {
        .size = {ENEMY_WIDTH, ENEMY_HEIGHT},
        .color = ENEMY_COLOR,
        .id = id,
    };
    //FIXME??
    if (setup_idle_enemy(enemy) < 0) return NULL;

    return enemy;
}

static int draw_enemy(Enemy const *visible_enemy) {
    if (visible_enemy == NULL) return -1;
    DrawRectangleV(visible_enemy->pos, visible_enemy->size, visible_enemy->color);
    return 0;
}

static int setup_move_enemy(Enemy *enemy) {
    if (enemy == NULL) return -1;

    enemy->velocity = calculate_enemy_velocity();
    enemy->is_visible = true;
    enemy->state = MOVING;

    return 0;
}

static int setup_idle_enemy(Enemy *enemy) {
    if (enemy == NULL) return -1;

    enemy->pos = calculate_enemy_start_pos(enemy->size);
    enemy->is_visible = false;
    enemy->velocity = 0.0f;
    enemy->state = IDLE;

    return 0;
}

static bool is_enemy_out_of_bound(Enemy const *enemy) {
    if (enemy == NULL) return false; //fixme
//fixme
    if ((enemy->pos.x + enemy->size.x) >= SCREEN_WIDTH ||
            enemy->pos.x < -100.0f ||
            (enemy->pos.y + enemy->size.y) >= SCREEN_HEIGHT ||
            enemy->pos.y < -100.0f )
        return true;

    return false;
}

static int move_enemy(Enemy *enemy) {
    if (enemy == NULL) return -1;
    enemy->pos.x += enemy->velocity;
    return 0;
}

static void free_enemy(Enemy **enemy) {
    if (enemy == NULL || *enemy == NULL) return;
    free(*enemy);
    *enemy = NULL;
}

Enemies *init_enemies() {
    Enemies *en;
    en = (Enemies *)malloc(sizeof(Enemies));
    if (en == NULL) return NULL;

    en->num_of_enemies = DEFAULT_ENEMIES_NUM;
    en->enemies = (Enemy **)malloc(sizeof(Enemy*) * en->num_of_enemies);
    if (en->enemies == NULL) {
        printf("ERRROR: coudnt alloc mem\n");
        free_enemies(&en);
        return NULL;
    }

    for (int i = 0; i < en->num_of_enemies; i++) {
        en->enemies[i] = init_enemy(i);

        if (en->enemies[i] == NULL) {
            free_enemies(&en);
            return NULL;
        }

    }

    return en;
}

int draw_enemies(Enemies const *enemies) {
    if (enemies == NULL) return -1;

    for (int i = 0; i < enemies->num_of_enemies; i++) {
        if (draw_enemy(enemies->enemies[i]) < 0) return -1;
    }

    return 0;
}

int update_enemies(Enemies *enemies, float delta_time) {
    float spawns_this_frame;
    int num_spawns;

    if (enemies == NULL) return -1;

    spawns_this_frame = BASE_ENEMY_SPAWN_RATE * delta_time;
    num_spawns = (int)spawns_this_frame;

    if ((float)rand() / RAND_MAX < (spawns_this_frame - num_spawns))
        num_spawns++;

    for (int s = 0; s < num_spawns; s++) {
        for (int i = 0; i < enemies->num_of_enemies; i++) {
            if (enemies->enemies[i]->state == IDLE) {
                setup_move_enemy(enemies->enemies[i]);
                break;
            }
        }
    }

    for (int i = 0; i < enemies->num_of_enemies; i++) {
        if (enemies->enemies[i]->state == MOVING) {
            if (is_enemy_out_of_bound(enemies->enemies[i]))
                setup_idle_enemy(enemies->enemies[i]);
            else
                move_enemy(enemies->enemies[i]);

        }
    }


    return 0;
}

void free_enemies(Enemies **enemies) {
    if (enemies == NULL || *enemies == NULL) return;

    for (int i = 0; i < (*enemies)->num_of_enemies; i++)
        free_enemy(&((*enemies)->enemies[i]));

    free(*enemies);
    *enemies = NULL;
}

