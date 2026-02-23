#include <time.h>
#include <stdio.h>
#include "ring.h"
#include "stdlib.h"
#include "settings.h"
#include "window_settings.h"

Ring_segment *init_ring_segment() {
    Ring_segment *ring_seg;

    ring_seg = (Ring_segment *)malloc(sizeof(Ring_segment));
    if (ring_seg == NULL) {
        printf("Error: coudnt alloc mem:");
        return NULL;
    }

    *ring_seg = (Ring_segment) {
        .color = DEFAULT_RING_SEG_COLOR,
        .segment_sharpness = DEFAULT_RING_SEG_SHARP,
        .start_angle = DEFAULT_RING_SEG_START_ANGLE,
        .end_angle = DEFAULT_RING_SEG_END_ANGLE,
        .state = ALIVE
    };

    return ring_seg;
}


Ring *init_ring() {
    Ring *ring;

    ring = (Ring *)malloc(sizeof(Ring));
    if (ring == NULL) {
        printf("Error: coudnt alloc nen");
        return NULL;
    }
    //FIXME
    ring->center = (Vector2) {
        SCREEN_WIDTH/2, SCREEN_HEIGHT/2
    };

    ring->inner_radius = RING_LITTLE_RADIUS,
          ring->outer_radius = RING_BIG_RADIUS;
    ring->segments_num = SEGMENTS_NUMBERS;

    ring->segments = (Ring_segment**)malloc(SEGMENTS_NUMBERS * sizeof(Ring_segment*));
    if (ring->segments == NULL) {
        printf("Error: couldnt alloc mem");
        free(ring);
        return NULL;
    }

    for (int i = 0; i < SEGMENTS_NUMBERS; i++) {
        ring->segments[i] = init_ring_segment();
        if (ring->segments[i] == NULL) {
            printf("Error: coudnt alloc mem");
            free_ring_segments(&(ring->segments));
            return NULL;
        }
    }

    //FIXME MB
    if (choose_picked_segment(ring) < 0) return NULL;

    return ring;
}

int add_segment_to_ring(Ring **ring) {
    Ring_segment **cur_seg;
    float seg_len, cur_seg_len;

    if (ring == NULL || *ring == NULL) {
        printf("ERROR: ring is NULL");
        return -1;
    }

    cur_seg = (*ring)->segments;
    cur_seg_len = 0.0f;

    seg_len = 360.0f / (float)SEGMENTS_NUMBERS;

    if (cur_seg == NULL) {
        printf("ERROR: cur_seg is NULL");
        return -1;
    }

    for (int i = 0; i < SEGMENTS_NUMBERS; i++) {
        cur_seg[i]->start_angle = cur_seg_len;
        cur_seg_len += seg_len;
        cur_seg[i]->end_angle = cur_seg_len;

        cur_seg[i]->color.r = 100 + i * 30;
        cur_seg[i]->color.g = 50 + i*i * 20;
        cur_seg[i]->color.b = 200 - i*i * 30;
        cur_seg[i]->color.r = 255;
    }

    if (cur_seg_len != 360.0f) printf( "all angle of ring not 360");

    return 0;
}

int draw_ring(Ring const *ring) {
    if (ring == NULL) return -1;

    for (int i = 0; i < SEGMENTS_NUMBERS; i++)
        DrawRing(ring->center,
                 ring->inner_radius,
                 ring->outer_radius,
                 ring->segments[i]->start_angle,
                 ring->segments[i]->end_angle,
                 DEFAULT_RING_SEG_SHARP,
                 ring->segments[i]->color);

    return 0;
}

int choose_picked_segment(Ring *ring) {
    int rand_seg_num;
    if (ring == NULL) return -1;

    rand_seg_num = rand() % SEGMENTS_NUMBERS;

    if (ring->segments[rand_seg_num] == NULL) return -1;

    ring->picked_segment = ring->segments[rand_seg_num];

    return 0;
}

int change_picked_segment_state(Ring *ring) {
    Ring_segment *cur;

    if (ring == NULL || ring->picked_segment == NULL) return -1;

    cur = ring->picked_segment;

    switch (cur->state) {
    case ALIVE:
        if (!mark_picked_segment(cur)) return -1;
        break;
    case MARKED:
        if (destroy_picked_segment(cur) < 0) return -1;
        break;
    case DESTROYED:
        if (revive_picked_segment(cur) < 0) return -1;
        if (choose_picked_segment(ring) < 0) return -1;
        break;

    }

    return 0;
}

int mark_picked_segment(Ring_segment *picked_segment) {
    if (picked_segment == NULL) return -1;
    picked_segment->state = MARKED;

    picked_segment->color = MARKED_PICKED_SEGMNET_COLOR;

    return 0;
}

int destroy_picked_segment(Ring_segment *picked_segment) {
    if (picked_segment == NULL) return -1;

    picked_segment->state = DESTROYED;

    picked_segment->color = DESTROYED_PICKED_SEGMNET_COLOR;

    return 0;
}

int revive_picked_segment(Ring_segment *picked_segment) {
    if (picked_segment == NULL) return -1;

    picked_segment->state = ALIVE;

    picked_segment->color = DEFAULT_RING_SEG_COLOR;

    return 0;
}

void free_ring_segments(Ring_segment ***segments) {
    Ring_segment **cur;

    if (segments == NULL || *segments == NULL || **segments == NULL) {
        printf("seg is null");
        return;
    }

    cur = *segments;
    for (int i = 0; i < SEGMENTS_NUMBERS; i++) 
        free(cur[i]);
    
    *segments = NULL;
}

void free_ring(Ring **ring) {
    if (ring == NULL || *ring == NULL) {
        printf("ring is null");
        return;
    }

    free_ring_segments(&((*ring)->segments));

    free(*ring);
}







