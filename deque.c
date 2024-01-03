#include <stdlib.h>
#include "include/deque.h"
#include "include/utils.h"

void deque_init(deque_t *deque, size_t capacity) {
    deque->length = 0;
    deque->capacity = capacity;
    deque->array = calloc(capacity, sizeof(card_t));
    if (deque->array == NULL)
        die("calloc");
    deque->front = deque ->rear = deque->array;
}

void deque_free(deque_t *deque) {
    free(deque->array);
}

card_t *deque_at(deque_t *deque, size_t index) {
    if (index >= deque->length)
        return NULL;
    card_t *ptr = deque->front + index;
    if (ptr >= deque->array + deque->capacity)
        ptr -= deque->capacity;
    return ptr;
}

void deque_push_front(deque_t *deque, card_t value) {
    if (deque->length == deque->capacity)
        return; // overflow
    if (deque->length) {
        if (deque->front == deque->array)
            deque->front = deque->array + deque->capacity;
        --deque->front;
    }
    ++deque->length;
    *deque->front = value;
}

void deque_push_rear(deque_t *deque, card_t value) {
    if (deque->length == deque->capacity)
        return; // overflow
    if (deque->length) {
        ++deque->rear;
        if (deque->rear == deque->array + deque->capacity)
            deque->rear = deque->array;
    }
    ++deque->length;
    *deque->rear = value;
}

