#include <stdlib.h>
#include <domino/deque.h>
#include <domino/utils.h>

void deque_init(deque_t *deque) {
    deque->length = 0;
    deque->capacity = DEQUE_MINIMUM_CAPACITY;
    deque->array = calloc(deque->capacity, sizeof(tile_t));
    if (deque->array == NULL)
        die("calloc");
    deque->front = deque ->rear = deque->array;
}

void deque_free(deque_t *deque) {
    free(deque->array);
}

tile_t *deque_at(deque_t *deque, size_t index) {
    if (index >= deque->length)
        return NULL;
    tile_t *ptr = deque->front + index;
    if (ptr >= deque->array + deque->capacity)
        ptr -= deque->capacity;
    return ptr;
}

void deque_push_front(deque_t *deque, tile_t tile) {
    if (deque->length == deque->capacity) {
        deque->capacity *= DEQUE_GROWTH_FACTOR;
        deque->array = realloc(deque->array, deque->capacity * sizeof(tile_t));
        if (deque->array == NULL)
            die("realloc");
    }
    if (deque->length) {
        if (deque->front == deque->array)
            deque->front = deque->array + deque->capacity;
        --deque->front;
    }
    ++deque->length;
    *deque->front = tile;
}

void deque_push_rear(deque_t *deque, tile_t tile) {
    if (deque->length == deque->capacity) {
        deque->capacity *= DEQUE_GROWTH_FACTOR;
        deque->array = realloc(deque->array, deque->capacity * sizeof(tile_t));
        if (deque->array == NULL)
            die("realloc");
    }
    if (deque->length) {
        ++deque->rear;
        if (deque->rear == deque->array + deque->capacity)
            deque->rear = deque->array;
    }
    ++deque->length;
    *deque->rear = tile;
}

