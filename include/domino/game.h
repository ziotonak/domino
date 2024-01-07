/**
 * @file
 * @brief File containing the definitions of a game.
 */
#pragma once

#include <stdbool.h>
#include <domino/deque.h>

/**
 * @brief A struct that contains the data needed to run a game of domino.
 */
typedef struct {
    bool running; /**< Is set to true if the game is running. */
    unsigned score; /**< Current score in the game. */
    unsigned round; /**< Current round in the game. */
    deque_t deque; /**< Double ended queue containing all the cards currently placed in the field. */
    unsigned count[6][6]; /**< Contains the current amount of cards remaining of each type. */
} game_t;

/**
 * @brief Initializes a new game.
 *
 * @param game the game to initialize.
 * @param cards the number of total cards used to play the game.
 */
void game_init(game_t *game, unsigned cards);

/**
 * @brief Function used to free a game.
 *
 * @param game the game to free.
 */
void game_free(game_t *game);

/**
 * @brief Function used to update the status of the game.
 *
 * Currently updates only the running flag.
 *
 * @param game the game.
 */
void game_update_flags(game_t *game);

/**
 * @brief Function used to push a card to the front of the playing field.
 *
 * If there are not enough cards of that type remaining the function does nothing.
 *
 * @param game the game.
 * @param card the type of card to push to the front.
 */
void game_push_front(game_t *game, card_t card);

/**
 * @brief Function used to push a card to the rear of the playing field
 *
 * If there are not enough cards of that type remaining the function does nothing.
 *
 * @param game the game.
 * @param card the type of card to push to the front.
 */
void game_push_rear(game_t *game, card_t card);