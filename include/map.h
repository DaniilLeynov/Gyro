#ifndef MAP
#define MAP
#if 0
#include <stdlib.h>
#include "raylib.h"
#include "ring.h"

typedef struct Map {
    Ring *ring;
    Enemy **enemys;
    Gem **gems;
    Shield **shields;
    Character *character;
} Map;

Map *init_map();

void destroy_map(Map **map);

void draw_map(Map const * const map);
#endif
#endif
