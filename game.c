#include <stdlib.h>
#include <string.h>
#include "game.h"

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
    unsigned front = game->deque.front->first - 1;
    for (int i = 0; i < 6; ++i)
        if (game->count[front][i])
            return;
    unsigned rear = game->deque.rear->second - 1;
    for (int i = 0; i < 6; ++i)
        if (game->count[rear][i])
            return;
    game->running = false;
}

void game_push_front(game_t *game, card_t card) {
    unsigned i = card.first - 1, j = card.second - 1;
    if (i < 0 || i >= 6 || j < 0 || j >= 6)
        return;
    if (game->count[i][j]) {
        if (game->deque.length && card.second != game->deque.front->first)
            return;
        --game->count[i][j];
        if (i != j)
            --game->count[j][i];
        game->score += card.first + card.second;
        ++game->round;
        deque_push_front(&game->deque, card);
    }
    game_update_flags(game);
}

void game_push_rear(game_t *game, card_t card) {
    unsigned i = card.first - 1, j = card.second - 1;
    if (i < 0 || i >= 6 || j < 0 || j >= 6)
        return;
    if (game->count[i][j]) {
        if (game->deque.length && card.first != game->deque.rear->second)
            return;
        --game->count[i][j];
        if (i != j)
            --game->count[j][i];
        game->score += card.first + card.second;
        ++game->round;
        deque_push_rear(&game->deque, card);
    }
    game_update_flags(game);
}

