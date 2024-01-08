#pragma once

#include <stdbool.h>
#include <domino/deque.h>

typedef struct {
    bool is_running;
    unsigned score;
    unsigned round;
    unsigned tile[6][6];
    deque_t deque;
} game_t;

void game_init(game_t *game, unsigned tiles);
void game_free(game_t *game);
void game_update_flags(game_t *game);
void game_push_front(game_t *game, tile_t tile);
void game_push_rear(game_t *game, tile_t tile);

