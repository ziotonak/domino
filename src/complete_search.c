#include <domino/complete_search.h>

unsigned _complete_search(game_t *game, unsigned count[6][6], unsigned rear, bool print) {
    tile_t card;
    unsigned score = 0;
    for (int i = 0; i < 6; ++i) {
        if (count[rear][i]) {
            count[i][rear] = --count[rear][i];
            unsigned value = _complete_search(game, count, i, false);
            value += rear + i + 2;
            if (value > score) {
                score = value;
                card.first = rear;
                card.second = i;
            }
            count[i][rear] = ++count[rear][i];
        }
    }
    if (print && score != 0) {
        unsigned i = card.first, j = card.second;
        count[i][j] = --count[j][i];
        ++card.first;
        ++card.second;
        game_push_rear(game, card);
        _complete_search(game, count, j, true);
        count[i][j] = ++count[j][i];
    }
    return score;
}

unsigned complete_search(game_t *game) {
    tile_t card;
    unsigned score = 0;
    unsigned count[6][6];
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            count[i][j] = game->tile[i][j];
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (count[i][j]) {
                count[i][j] = --count[j][i];
                unsigned value = _complete_search(game, count, j, false);
                value += i + j + 2;
                if (value > score) {
                    score = value;
                    card.first = i;
                    card.second = j;
                }
                count[i][j] = ++count[j][i];
            }
        }
    }
    if (score != 0) {
        unsigned j = card.second;
        count[card.first][card.second] = --count[card.second][card.first];
        ++card.first;
        ++card.second;
        game_push_rear(game, card);
        _complete_search(game, count, j, true);
    }
    return score;
}

