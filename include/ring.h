#ifndef RING
#define RING

#include "raylib.h"

typedef enum State State;

typedef struct Ring_segment Ring_segment;
typedef struct Ring Ring;

Ring *init_ring();

int draw_ring(Ring const *ring);

int choose_picked_segment(Ring *ring);

int change_picked_segment_state(Ring *ring);

void free_ring(Ring **ring);

#endif
