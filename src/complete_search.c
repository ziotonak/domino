#include <string.h>
#include <domino/complete_search.h>

static unsigned _complete_search(
    game_t *game,
    unsigned tile[6][6], 
    unsigned rear,
    bool confirm
) {
    unsigned max_i, max_j;
    unsigned max_score = 0;

    for (int i = 0; i < 6; ++i) {
        if (tile[rear][i]) {

            // place the tile
            tile[rear][i] = --tile[i][rear];

            unsigned score = _complete_search(game, tile, i, false);
            score += rear + 1;
            score += i + 1;

            // update the best score
            if (score > max_score) {
                max_score = score;
                max_i = rear;
                max_j = i;
            }

            // remove the tile
            tile[rear][i] = ++tile[i][rear];
        }
    }

    // confirm the optimal placement
    if (confirm && max_score != 0) {
        tile[max_i][max_j] = --tile[max_j][max_i];

        tile_t max_tile = {max_i + 1, max_j + 1};
        game_push_rear(game, max_tile);

        _complete_search(game, tile, max_j, true);

        tile[max_i][max_j] = ++tile[max_j][max_i];
    }

    return max_score;
}

void complete_search(game_t *game) {
    unsigned tile[6][6];
    memcpy(tile, game->tile, sizeof(tile));

    unsigned max_i, max_j;
    unsigned max_score = 0;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (!tile[i][j])
                continue;

            // place the tile
            tile[i][j] = --tile[j][i];

            unsigned score = _complete_search(game, tile, j, false);
            score += i + 1;
            score += j + 1;

            // update the best score
            if (score > max_score) {
                max_score = score;
                max_i = i;
                max_j = j;
            }

            // remove the tile
            tile[i][j] = ++tile[j][i];

        }
    }

    // confirm the optimal placement
    if (max_score != 0) {
        tile[max_i][max_j] = --tile[max_j][max_i];

        tile_t max_tile = {max_i + 1, max_j + 1};
        game_push_rear(game, max_tile);

        _complete_search(game, tile, max_j, true);
    }
}

