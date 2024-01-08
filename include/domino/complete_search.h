/**
 * @file complete_search.h
 * @brief Implementation of a complete search strategy for the linear domino game.
 */

#pragma once

#include <domino/game.h>

/**
 * @brief Recursively finds the optimal solution for a linear domino game 
 *        using complete search.
 *
 * This function performs a complete search to find the optimal placement of
 * domino tiles on the game board. It uses recursion to explore all possible
 * combinations and returns the maximum score achievable.
 *
 * @param[in] game - The linear domino game structure.
 */
void complete_search(game_t *game);

