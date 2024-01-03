#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "deque.h"

typedef struct {
    bool running;
    unsigned score;
    unsigned round;
    deque_t deque;
    unsigned count[6][6];
} game_t;

void game_init(game_t *game, unsigned cards);
void game_free(game_t *game);
void game_update_flags(game_t *game);
void game_push_front(game_t *game, card_t card);
void game_push_rear(game_t *game, card_t card);

#endif // GAME_H
