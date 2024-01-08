#include <stdlib.h>
#include <domino/deque.h>
#include <domino/error_handling.h>

void deque_init(deque_t *deque) {
    deque->length = 0;
    deque->capacity = DEQUE_MINIMUM_CAPACITY;
    deque->array = calloc(deque->capacity, sizeof(tile_t));
    if (deque->array == NULL)
        die("calloc");
    deque->front = deque->rear = deque->array;
}

void deque_free(deque_t *deque) {
    free(deque->array);
}

tile_t *deque_at(const deque_t *deque, size_t index) {
    if (index >= deque->length)
        return NULL;
    tile_t *ptr = deque->front + index;
    if (ptr >= deque->array + deque->capacity)
        ptr -= deque->capacity;
    return ptr;
}

static void _deque_resize(deque_t *deque, size_t capacity) {
    if (capacity < deque->length)
        return;

    tile_t *array = calloc(capacity, sizeof(tile_t));
    if (array == NULL)
        die("calloc");

    tile_t *new = array;
    tile_t *old = deque->front;
    while (old != deque->rear) {
        *new++ = *old++;
        if (old == deque->array + deque->capacity)
            old = deque->array;
    }
    *new = *old;

    free(deque->array);
    deque->capacity = capacity;
    deque->front = deque->rear = deque->array = array;
    if (deque->length)
        deque->rear += deque->length - 1;
}

static inline void _deque_grow(deque_t *deque) {
    _deque_resize(deque, deque->capacity * DEQUE_GROWTH_FACTOR);
}

static void _deque_shrink(deque_t *deque) {
    if (deque->capacity <= DEQUE_MINIMUM_CAPACITY)
        return;
    _deque_resize(deque, deque->capacity / DEQUE_GROWTH_FACTOR);
}

void deque_push_front(deque_t *deque, tile_t tile) {
    if (deque->length == deque->capacity)
        _deque_grow(deque);
    if (deque->length) {
        if (deque->front == deque->array)
            deque->front = deque->array + deque->capacity;
        --deque->front;
    }
    ++deque->length;
    *deque->front = tile;
}

void deque_push_rear(deque_t *deque, tile_t tile) {
    if (deque->length == deque->capacity)
        _deque_grow(deque);
    if (deque->length) {
        ++deque->rear;
        if (deque->rear == deque->array + deque->capacity)
            deque->rear = deque->array;
    }
    ++deque->length;
    *deque->rear = tile;
}

void deque_pop_front(deque_t *deque) {
    if (deque->length) {
        if (deque->length > 1) {
            ++deque->front;
            if (deque->front == deque->array + deque->capacity)
                deque->front = deque->array;
        }
        --deque->length;
        if (deque->length * DEQUE_GROWTH_FACTOR <= deque->capacity)
            _deque_shrink(deque);
    }
}

void deque_pop_rear(deque_t *deque) {
    if (deque->length) {
        if (deque->length > 1) {
            if (deque->rear == deque->array)
                deque->rear = deque->array + deque->capacity;
            --deque->rear;
        }
        --deque->length;
        if (deque->length * DEQUE_GROWTH_FACTOR <= deque->capacity)
            _deque_shrink(deque);
    }
}

