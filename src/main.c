#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <domino/game.h>
#include <domino/complete_search.h>

void draw_screen(game_t *game) {
    printf("\x1b[2J\x1b[H"); // clear screen and move cursor

    printf("Score: %u\n", game->score); 
    printf("Round: %u\n", game->round);

    for (unsigned int i = 0; i < 6; ++i) {
        for (unsigned int j = i; j < 6; ++j) {
            // check if this move can be performed in this turn, flipped or not
            bool valid = game->tile[i][j];
            if (game->deque.length)
                valid &= (game->deque.rear->second == i + 1 || game->deque.rear->second == j + 1 
                    || game->deque.front->first == i + 1 || game->deque.front->first == j + 1);

            if (valid)
                printf("\x1b[92m"); // set foreground color to green
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

void run_normal(game_t *game) {
    draw_screen(game);
    while (game->is_running) {
        int c;
        tile_t tile;

        bool erase = false;
        do {
            if (erase)
                printf("\x1b[1A\x1b[2K\x1b[999D\x1b[91m");
            erase = true;

            printf("Left [1-6]:\x1b[0m ");

            while ((c = getchar()) != EOF && c == '\n');

            char a;
            while ((a = getchar()) != EOF && a != '\n');
        } while (c < '1' || c > '6');
        tile.first = c - '0';

        erase = false;
        do {
            if (erase)
                printf("\x1b[1A\x1b[2K\x1b[999D\x1b[91m");
            erase = true;

            printf("Right [1-6]:\x1b[0m ");

            while ((c = getchar()) != EOF && c == '\n');

            char a;
            while ((a = getchar()) != EOF && a != '\n');
        } while (c < '1' || c > '6');
        tile.second = c - '0';

        erase = false;
        do {
            if (erase)
                printf("\x1b[1A\x1b[2K\x1b[999D\x1b[91m");
            erase = true;

            printf("Push front/rear [f/r]:\x1b[0m ");

            while ((c = getchar()) != EOF && c == '\n');

            char a;
            while ((a = getchar()) != EOF && a != '\n');
        } while (c != 'f' && c != 'r');

        if (c == 'f')
            game_push_front(game, tile);
        else
            game_push_rear(game, tile);

        draw_screen(game);
    }
}

void run_auto(game_t *game) {
    complete_search(game);
    draw_screen(game);
}

int main() {
    srand((unsigned) time(NULL));

    char c;
    bool erase = false;
    do {
        if (erase)
            printf("\x1b[1A\x1b[2K\x1b[999D\x1b[91m");
        erase = true;

        printf("Interactive/auto [i/a]:\x1b[0m ");

        while ((c = getchar()) != EOF && c == '\n');

        char a;
        while ((a = getchar()) != EOF && a != '\n');
    } while (c != 'i' && c != 'a');
 
    game_t game;
    game_init(&game, 16);
    if (c == 'i')
        run_normal(&game);
    else
        run_auto(&game);
    game_free(&game);
}

