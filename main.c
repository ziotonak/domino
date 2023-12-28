#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint8_t f, s;
} card_t;

typedef struct {
    size_t length, capacity;
    card_t *array, *front, *rear;
} deque_t;

void die(const char *message) {
    perror(message);
    exit(1);
}

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

typedef struct {
    uint64_t score;
    deque_t deque;
} game_t;

void game_init(game_t *game) {
    game->score = 0;
    deque_init(&game->deque, 5);
}

void game_free(game_t *game) {
    deque_free(&game->deque);
}

void game_push_front(game_t *game) {
}

void game_push_rear(game_t *game) {
}

void game_draw_screen(game_t *game) {
    printf("\x1b[2J\x1b[H"); // clear screen and move cursor
    if (game->deque.length) {
        for (size_t i = 0; i < game->deque.length; ++i) {
            card_t card = *deque_at(&game->deque, i);
            printf("[%d|%d] ", card.f, card.s);
        }
        putchar('\n');
    }
}

int main() {
    game_t game;
    game_init(&game);

    while (1)
        game_draw_screen(&game);

    game_free(&game);
}

