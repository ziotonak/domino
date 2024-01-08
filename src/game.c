#include <stdlib.h>
#include <string.h>
#include <domino/game.h>

void game_init(game_t *game, unsigned tiles) {
    game->score = 0;
    game->round = 1;
    deque_init(&game->deque);
    memset(game->tile, 0, sizeof(game->tile));
    while (tiles--) {
        int i = rand() % 6, j = rand() % 6;
        game->tile[j][i] = ++game->tile[i][j];
    }
    game_update_flags(game);
}

void game_free(game_t *game) {
    deque_free(&game->deque);
}

void game_update_flags(game_t *game) {
    game->is_running = true;
    if (game->deque.length) {
        unsigned front = game->deque.front->first - 1;
        for (int i = 0; i < 6; ++i)
            if (game->tile[front][i])
                return;
        unsigned rear = game->deque.rear->second - 1;
        for (int i = 0; i < 6; ++i)
            if (game->tile[rear][i])
                return;
        game->is_running = false;
    }
}

void game_push_front(game_t *game, tile_t tile) {
    unsigned i = tile.first - 1, j = tile.second - 1;
    if (i >= 6 || j >= 6)
        return;
    if (game->tile[i][j]) {
        if (game->deque.length && tile.second != game->deque.front->first)
            return;
        --game->tile[i][j];
        if (i != j)
            --game->tile[j][i];
        game->score += tile.first + tile.second;
        ++game->round;
        deque_push_front(&game->deque, tile);
        game_update_flags(game);
    }
}

void game_push_rear(game_t *game, tile_t tile) {
    unsigned i = tile.first - 1, j = tile.second - 1;
    if (i >= 6 || j >= 6)
        return;
    if (game->tile[i][j]) {
        if (game->deque.length && tile.first != game->deque.rear->second)
            return;
        --game->tile[i][j];
        if (i != j)
            --game->tile[j][i];
        game->score += tile.first + tile.second;
        ++game->round;
        deque_push_rear(&game->deque, tile);
        game_update_flags(game);
    }
}

