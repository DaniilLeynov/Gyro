#ifndef ENTITYS
#define ENTITYS

#include "raylib.h"

typedef struct Shape {
    float radius;
} Shape;


typedef struct Entity {
    Color color;
    int velocity;
    Shape shape;
    Vector2 pos;
} Entity;


#endif
