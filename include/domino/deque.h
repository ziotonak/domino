#pragma once

#include <stddef.h>
#include <domino/tile.h>

#define DEQUE_GROWTH_FACTOR 2
#define DEQUE_MINIMUM_CAPACITY 2

typedef struct {
    size_t length;
    size_t capacity;
    tile_t *array;
    tile_t *front;
    tile_t *rear;
} deque_t;

void deque_init(deque_t *deque);
void deque_free(deque_t *deque);
tile_t *deque_at(deque_t *deque, size_t index);
void deque_push_front(deque_t *deque, tile_t tile);
void deque_push_rear(deque_t *deque, tile_t tile);

