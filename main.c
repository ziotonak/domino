#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char f, s;
} card_t;

typedef struct {
    size_t length, capacity;
    card_t *array, *front, *rear;
} deque_t;

int deque_init(deque_t *deque, size_t capacity) {
    deque->length = 0;
    deque->capacity = capacity;
    deque->array = calloc(capacity, sizeof(card_t));
    if (deque->array == NULL)
        return -1;
    deque->front = deque ->rear = deque->array;
    return 0;
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

int main() {
    deque_t deque;
    deque_init(&deque, 15);

    for (int i=0; i<200; ++i) {
        card_t card = {i % 6, 6 - i % 6};
        if (i & 1) deque_push_rear(&deque, card);
        else deque_push_front(&deque, card);
    }

    if (deque.length) {
        for (size_t i=0; i<deque.length; ++i) {
            card_t card = *deque_at(&deque, i);
            printf("[%d|%d] ", card.f, card.s);
        }
        putchar('\n');
    }

    deque_free(&deque);
}

