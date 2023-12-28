#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct {
    size_t length, capacity;
    T *array, *front, *rear;
} deque_t;

int deque_init(deque_t *deque, size_t capacity) {
    deque->length = 0;
    deque->capacity = capacity;
    deque->array = calloc(capacity, sizeof(T));
    if (deque->array == NULL)
        return -1;
    deque->front = deque ->rear = deque->array;
    return 0;
}

void deque_free(deque_t *deque) {
    free(deque->array);
}

T *deque_at(deque_t *deque, size_t index) {
    if (index >= deque->length)
        return NULL;
    T *ptr = deque->front + index;
    if (ptr >= deque->array + deque->capacity)
        ptr -= deque->capacity;
    return ptr;
}

void deque_push_front(deque_t *deque, T value) {
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

void deque_push_rear(deque_t *deque, T value) {
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
        if (i & 1) deque_push_rear(&deque, i);
        else deque_push_front(&deque, i);
    }

    if (deque.length) {
        for (size_t i=0; i<deque.length; ++i)
            printf("%d ", *deque_at(&deque, i));
        putchar('\n');
    }

    deque_free(&deque);
}

