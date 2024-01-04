#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "game.h"

unsigned long cards = 16; /**< The number of cards the player will have at the start of the game. */
enum {DEFAULT, AUTO} mode = DEFAULT; /**< Current mode of the game. If set to auto an ai is used to play the game. */

/**
 * @brief Function used to handle the input of the player when playing in interactive mode.
 *
 * @param game the game.
 */
void handle_input(game_t *game) {
    card_t card;
    printf("Insert card (two space separated numbers, order matters): ");
    scanf("%u", &card.first);
    scanf("%u", &card.second);

    printf("Push left or right ('l' for left or 'r' for right): ");
    char c = tolower(getchar());
    while (c != 'l' && c != 'r')
        c = tolower(getchar());

    if (c == 'l')
        game_push_front(game, card);
    else
        game_push_rear(game, card);
}

/**
 * @brief Function used to display the playing field.
 *
 * @param game the game.
 */
void draw_screen(game_t *game) {
    printf("\x1b[2J\x1b[H"); // clear screen and move cursor

    printf("Score: %u\n", game->score); 
    printf("Round: %u\n", game->round);

    for (int i = 0; i < 6; ++i) {
        for (int j = i; j < 6; ++j) {
            // check if this move can be performed in this turn, flipped or not
            bool valid = game->deque.length && game->count[i][j]
                && (game->deque.rear->second == i + 1 || game->deque.rear->second == j + 1 
                || game->deque.front->first == i + 1 || game->deque.front->first == j + 1);

            if (valid)
                printf("\x1b[32m"); // set foreground color to green
            printf("%u [%d|%d]\x1b[0m   ", game->count[i][j], i + 1, j + 1);
        }
        putchar('\n');
    }

    if (game->deque.length) {
        for (size_t i = 0; i < game->deque.length; ++i) {
            card_t card = *deque_at(&game->deque, i);
            printf("[%u|%u] ", card.first, card.second);
        }
        putchar('\n');
    }
}

/**
 * @brief Function used to parse the arguments passed to the program.
 *
 * Sets the global config variables based on the arguments passed to the program.
 * Prints an help message and quits if detects illegal arguments.
 *
 * @param argc the argument count.
 * @param argv the values of the arguments.
 */
void parse_args(int argc, char *argv[]) {
    bool help = false;

    for (size_t opt = 1; opt < argc; ++opt) {
        if (argv[opt][0] == '-') {
            switch (argv[opt][1]) {
                case '-': {
                    const char *arg = argv[opt] + 2;
                    if (strcmp("help", arg) == 0)
                        help = true;
                    else if (strcmp("auto", arg) == 0)
                        mode = AUTO;
                    else
                        help = true;
                    break;
                }
                case 'a':
                    mode = AUTO;
                    break;
                case 'h':
                default:
                    help = true;
                    break;
            }
        } else {
            unsigned long value = strtoul(argv[opt], NULL, 0);
            if (value && errno != ERANGE)
                cards = value;
            else
                help = true;
        }
    }

    if (help) {
        printf("Usage: %s [-h | --help] [-a | --auto] [cards]\n", argv[0]);
        exit(0);
    }
}

unsigned _solve(game_t *game, unsigned count[6][6], unsigned rear, bool print) {
    card_t card;
    unsigned score = 0;
    for (int i = 0; i < 6; ++i) {
        if (count[rear][i]) {
            count[i][rear] = --count[rear][i];
            unsigned value = _solve(game, count, i, false);
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
        _solve(game, count, j, true);
        count[i][j] = ++count[j][i];
    }
    return score;
}

/**
 * @brief Solves the game using a complete search strategy.
 *
 * @param game the game to solve.
 */
unsigned solve(game_t *game) {
    card_t card;
    unsigned score = 0;
    unsigned count[6][6];
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            count[i][j] = game->count[i][j];
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (count[i][j]) {
                count[i][j] = --count[j][i];
                unsigned value = _solve(game, count, j, false);
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
        _solve(game, count, j, true);
    }
    return score;
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    srand((unsigned) time(NULL));

    game_t game;
    game_init(&game, cards);

    if (mode == DEFAULT) {
        while (game.running) {
            draw_screen(&game);
            handle_input(&game);
        }
        draw_screen(&game);
    } else {
        solve(&game);
        draw_screen(&game);
    }

    game_free(&game);
}

