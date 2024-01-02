#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/*** Deque ***/

typedef struct {
    unsigned f, s;
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

/*** Game ***/

typedef struct {
    bool running;
    unsigned score;
    unsigned round;
    deque_t deque;
    unsigned count[6][6];
} game_t;

void game_init(game_t *game, unsigned cards) {
    game->running = true;
    game->score = 0;
    game->round = 1;
    deque_init(&game->deque, cards + 5);
    memset(game->count, 0, sizeof(game->count));
    while (cards--) {
        int i = rand() % 6, j = rand() % 6;
        game->count[j][i] = ++game->count[i][j];
    }
}

void game_free(game_t *game) {
    deque_free(&game->deque);
}

void game_update_flags(game_t *game) {
    if (!game->deque.length)
        return;
    unsigned front = game->deque.front->f - 1;
    for (int i = 0; i < 6; ++i)
        if (game->count[front][i])
            return;
    unsigned rear = game->deque.rear->s - 1;
    for (int i = 0; i < 6; ++i)
        if (game->count[rear][i])
            return;
    game->running = false;
}

void game_push_front(game_t *game, card_t card) {
    unsigned i = card.f - 1, j = card.s - 1;
    if (i < 0 || i >= 6 || j < 0 || j >= 6)
        return;
    if (game->count[i][j]) {
        if (game->deque.length && card.s != game->deque.front->f)
            return;
        --game->count[i][j];
        if (i != j)
            --game->count[j][i];
        game->score += card.f + card.s;
        ++game->round;
        deque_push_front(&game->deque, card);
    }
    game_update_flags(game);
}

void game_push_rear(game_t *game, card_t card) {
    unsigned i = card.f - 1, j = card.s - 1;
    if (i < 0 || i >= 6 || j < 0 || j >= 6)
        return;
    if (game->count[i][j]) {
        if (game->deque.length && card.f != game->deque.rear->s)
            return;
        --game->count[i][j];
        if (i != j)
            --game->count[j][i];
        game->score += card.f + card.s;
        ++game->round;
        deque_push_rear(&game->deque, card);
    }
    game_update_flags(game);
}

/*** Input ***/

void handle_input(game_t *game) {
    card_t card;
    printf("Insert card: ");
    scanf("%u", &card.f);
    scanf("%u", &card.s);

    printf("Push L/r: ");
    char c = tolower(getchar());
    while (c != 'l' && c != 'r')
        c = tolower(getchar());

    if (c == 'l')
        game_push_front(game, card);
    else
        game_push_rear(game, card);
}

/*** Output ***/

void draw_screen(game_t *game) {
    printf("\x1b[2J\x1b[H"); // clear screen and move cursor

    printf("Score: %u\n", game->score); 
    printf("Round: %u\n", game->round);

    for (int i = 0; i < 6; ++i) {
        for (int j = i; j < 6; ++j) {
            // check if this move can be performed in this turn, flipped or not
            bool valid = game->deque.length && game->count[i][j]
                && (game->deque.rear->s == i + 1 || game->deque.rear->s == j + 1 
                || game->deque.front->f == i + 1 || game->deque.front->f == j + 1);

            if (valid)
                printf("\x1b[32m"); // set foreground color to green
            printf("%u [%d|%d]\x1b[0m   ", game->count[i][j], i + 1, j + 1);
        }
        putchar('\n');
    }

    if (game->deque.length) {
        for (size_t i = 0; i < game->deque.length; ++i) {
            card_t card = *deque_at(&game->deque, i);
            printf("[%u|%u] ", card.f, card.s);
        }
        putchar('\n');
    }
}

/*** Main ***/

int main() {
    srand((unsigned) time(NULL));

    game_t game;
    game_init(&game, 16);

    while (game.running) {
        draw_screen(&game);
        handle_input(&game);
    }
    draw_screen(&game);

    game_free(&game);
}

