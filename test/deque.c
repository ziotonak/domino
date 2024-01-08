#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <domino/deque.h>

#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s\n", #condition); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

void test_deque_initialization() {
    puts("test_deque_push_rear");

    deque_t deque;
    deque_init(&deque);

    ASSERT(deque.length == 0);
    ASSERT(deque.capacity >= DEQUE_MINIMUM_CAPACITY);
    ASSERT(deque.array != NULL);
    ASSERT(deque.front == deque.array);
    ASSERT(deque.rear == deque.array);

    deque_free(&deque);
}

void test_deque_push_front() {
    puts("test_deque_push_front");

    deque_t deque;
    deque_init(&deque);

    tile_t tile1 = {1, 'A'};
    tile_t tile2 = {2, 'B'};

    deque_push_front(&deque, tile1);
    ASSERT(deque.length == 1);
    ASSERT(deque.front->first == 1);
    ASSERT(deque.rear->first == 1);

    deque_push_front(&deque, tile2);
    ASSERT(deque.length == 2);
    ASSERT(deque.front->first == 2);
    ASSERT(deque.rear->first == 1);

    deque_free(&deque);
}

void test_deque_push_rear() {
    puts("test_deque_push_rear");

    deque_t deque;
    deque_init(&deque);

    tile_t tile1 = {1, 'A'};
    tile_t tile2 = {2, 'B'};

    deque_push_rear(&deque, tile1);
    ASSERT(deque.length == 1);
    ASSERT(deque.front->first == 1);
    ASSERT(deque.rear->first == 1);

    deque_push_rear(&deque, tile2);
    ASSERT(deque.length == 2);
    ASSERT(deque.front->first == 1);
    ASSERT(deque.rear->first == 2);

    deque_free(&deque);
}

void test_deque_pop_front() {
    puts("test_deque_pop_front");

    deque_t deque;
    deque_init(&deque);

    tile_t tile1 = {1, 'A'};
    tile_t tile2 = {2, 'B'};

    deque_push_front(&deque, tile1);
    deque_push_front(&deque, tile2);

    deque_pop_front(&deque);
    ASSERT(deque.length == 1);
    ASSERT(deque.front->first == 1);
    ASSERT(deque.rear->first == 1);

    deque_pop_front(&deque);
    ASSERT(deque.length == 0);
    ASSERT(deque.front == deque.rear);
    ASSERT(deque.array == deque.front);

    deque_free(&deque);
}

void test_deque_pop_rear() {
    puts("test_deque_pop_rear");

    deque_t deque;
    deque_init(&deque);

    tile_t tile1 = {1, 'A'};
    tile_t tile2 = {2, 'B'};

    deque_push_rear(&deque, tile1);
    deque_push_rear(&deque, tile2);

    deque_pop_rear(&deque);
    ASSERT(deque.length == 1);
    ASSERT(deque.front->first == 1);
    ASSERT(deque.rear->first == 1);

    deque_pop_rear(&deque);
    ASSERT(deque.length == 0);
    ASSERT(deque.front == deque.rear);
    ASSERT(deque.array == deque.front);

    deque_free(&deque);
}

void test_deque_dynamic_resize() {
    puts("test_deque_dynamic_resize");

    deque_t deque;
    deque_init(&deque);

    // Push elements until resizing occurs
    for (unsigned i = 0; i < DEQUE_MINIMUM_CAPACITY * DEQUE_GROWTH_FACTOR + 1; ++i) {
        deque_push_rear(&deque, (tile_t){i, 'A' + i});
    }

    ASSERT(deque.length == DEQUE_MINIMUM_CAPACITY * DEQUE_GROWTH_FACTOR + 1);
    ASSERT(deque.capacity >= DEQUE_MINIMUM_CAPACITY * DEQUE_GROWTH_FACTOR + 1);

    // Pop elements to trigger shrinking
    for (int i = 0; i < DEQUE_MINIMUM_CAPACITY * DEQUE_GROWTH_FACTOR; ++i) {
        deque_pop_front(&deque);
    }

    ASSERT(deque.length == 1);
    ASSERT(deque.capacity >= DEQUE_MINIMUM_CAPACITY);
    ASSERT(deque.capacity < DEQUE_MINIMUM_CAPACITY * DEQUE_GROWTH_FACTOR);

    deque_free(&deque);
}

void test_deque() {
    test_deque_initialization();
    test_deque_push_front();
    test_deque_push_rear();
    test_deque_pop_front();
    test_deque_pop_rear();
    test_deque_dynamic_resize();
    puts("All tests passed!");
}

int main() {
    test_deque();
}

