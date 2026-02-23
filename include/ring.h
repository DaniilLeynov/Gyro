#ifndef RING
#define RING

// ring is part of map

#include "raylib.h"

typedef enum State {
    ALIVE,
    MARKED,
    DESTROYED,
} State;

typedef struct Ring_segment {
    Color color;
    float segment_sharpness;
    float start_angle;
    float end_angle;
    State state; //
} Ring_segment;

typedef struct Ring {
    int segments_num;
    Vector2 center;
    float inner_radius;
    float outer_radius;
    Ring_segment **segments;
    Ring_segment *picked_segment; //сегмент который должен изменить свои цвета а затем удален.
} Ring;

Ring_segment *init_ring_segment();

Ring *init_ring();

int add_segment_to_ring(Ring **ring);

int draw_ring(Ring const *ring);

int choose_picked_segment(Ring *ring);

int change_picked_segment_state(Ring *ring);

int mark_picked_segment(Ring_segment *picked_segment);

int destroy_picked_segment(Ring_segment *picked_segment);

int revive_picked_segment(Ring_segment *picked_segment);

void free_ring_segments(Ring_segment ***segments);

void free_ring(Ring **ring);

#endif
