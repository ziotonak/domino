/**
 * @file game.h
 * @brief Implementation of the linear domino game.
 */

#pragma once

#include <stdbool.h>
#include <domino/deque.h>

/**
 * @struct game_t
 * @brief Structure representing a linear domino game.
 */
typedef struct {
    bool is_running;      /**< Flag indicating whether the game is running. */
    unsigned score;       /**< Current score of the game. */
    unsigned round;       /**< Current round of the game. */
    unsigned tile[6][6];  /**< Matrix representing the available tiles. */
    deque_t deque;        /**< Deque used to manage placed tiles in the game. */
} game_t;

/**
 * @brief Initializes the Linear Domino game with a given number of tiles.
 * 
 * Initializes the game structure, the score, and the round and randomly
 * generates tiles.
 * 
 * @param[in,out] game Pointer to the game structure.
 * @param[in] tiles Number of random tiles to initialize the game with.
 */
void game_init(game_t *game, unsigned tiles);

/**
 * @brief Frees resources allocated for a linear domino game.
 * 
 * Frees the deque used in the game structure.
 * 
 * @param[in,out] game Pointer to the game structure.
 */
void game_free(game_t *game);

/**
 * @brief Updates the game flags.
 * 
 * Checks if the game is still running by examining the tiles 
 * on the front and rear of the deque.
 * 
 * @param[in,out] game Pointer to the game structure.
 */
void game_update_flags(game_t *game);

/**
 * @brief Pushes a tile to the front of the deque.
 * 
 * Pushes a tile to the front of the deque if it is a valid move.
 * 
 * @param[in,out] game Pointer to the game structure.
 * @param[in] tile The tile to be pushed to the front.
 */
void game_push_front(game_t *game, tile_t tile);

/**
 * @brief Pushes a tile to the rear of the deque.
 * 
 * Pushes a tile to the rear of the deque if it is a valid move.
 * 
 * @param[in,out] game Pointer to the game structure.
 * @param[in] tile The tile to be pushed to the rear.
 */
void game_push_rear(game_t *game, tile_t tile);

