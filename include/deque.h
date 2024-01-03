#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>
#include "card.h"

typedef struct {
    size_t length, capacity;
    card_t *array, *front, *rear;
} deque_t;

void deque_init(deque_t *deque, size_t capacity);
void deque_free(deque_t *deque);
card_t *deque_at(deque_t *deque, size_t index);
void deque_push_front(deque_t *deque, card_t value);
void deque_push_rear(deque_t *deque, card_t value);

#endif // DEQUE_H
