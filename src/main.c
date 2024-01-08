#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <domino/game.h>
#include <domino/complete_search.h>

unsigned long cards = 16;
enum {DEFAULT, AUTO} mode = DEFAULT;

void handle_input(game_t *game) {
    tile_t tile;
    printf("Insert tile (two space separated numbers, order matters): ");
    scanf("%u", &tile.first);
    scanf("%u", &tile.second);

    printf("Push left or right ('l' for left or 'r' for right): ");
    char c = tolower(getchar());
    while (c != 'l' && c != 'r')
        c = tolower(getchar());

    if (c == 'l')
        game_push_front(game, tile);
    else
        game_push_rear(game, tile);
}

void draw_screen(game_t *game) {
    printf("\x1b[2J\x1b[H"); // clear screen and move cursor

    printf("Score: %u\n", game->score); 
    printf("Round: %u\n", game->round);

    for (unsigned int i = 0; i < 6; ++i) {
        for (unsigned int j = i; j < 6; ++j) {
            // check if this move can be performed in this turn, flipped or not
            bool valid = game->deque.length && game->tile[i][j]
                && (game->deque.rear->second == i + 1 || game->deque.rear->second == j + 1 
                || game->deque.front->first == i + 1 || game->deque.front->first == j + 1);

            if (valid)
                printf("\x1b[32m"); // set foreground color to green
            printf("%u [%d|%d]\x1b[0m   ", game->tile[i][j], i + 1, j + 1);
        }
        putchar('\n');
    }

    if (game->deque.length) {
        for (size_t i = 0; i < game->deque.length; ++i) {
            tile_t tile = *deque_at(&game->deque, i);
            printf("[%u|%u] ", tile.first, tile.second);
        }
        putchar('\n');
    }
}

void parse_args(int argc, char *argv[]) {
    bool help = false;

    for (int opt = 1; opt < argc; ++opt) {
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

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    srand((unsigned) time(NULL));

    game_t game;
    game_init(&game, cards);

    if (mode == DEFAULT) {
        while (game.is_running) {
            draw_screen(&game);
            handle_input(&game);
        }
        draw_screen(&game);
    } else {
        complete_search(&game);
        draw_screen(&game);
    }

    game_free(&game);
}

