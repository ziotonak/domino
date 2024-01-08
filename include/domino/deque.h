/**
 * @file deque.h
 * @brief A simple double-ended queue (deque) implementation.
 *
 * This file defines functions for initializing, manipulating, and freeing a
 * deque. The deque dynamically adjusts its capacity to accommodate varying 
 * numbers of elements efficiently.
 *
 * @note This implementation uses circular array-based storage for better
 * efficiency in pushing and popping elements at both ends of the deque.
 * @note The capacity of the deque is adjusted dynamically to optimize memory usage.
 */

#pragma once

#include <stddef.h>
#include <domino/tile.h>

/**
 * @def DEQUE_GROWTH_FACTOR
 * @brief The growth factor used to increase the capacity of the deque.
 */
#define DEQUE_GROWTH_FACTOR 2

/**
 * @def DEQUE_MINIMUM_CAPACITY
 * @brief The minimum capacity of the deque.
 */
#define DEQUE_MINIMUM_CAPACITY 2


/**
 * @struct deque_t
 * @brief Structure representing a double-ended queue.
 */
typedef struct {
    size_t length;    /**< Current number of elements in the deque. */
    size_t capacity;  /**< Capacity of the deque's internal array. */
    tile_t *array;    /**< Pointer to the internal array holding elements. */
    tile_t *front;    /**< Pointer to the front of the deque. */
    tile_t *rear;     /**< Pointer to the rear of the deque. */
} deque_t;

/**
 * @brief Initializes a deque.
 *
 * Allocates memory for the internal array and sets initial values for the deque.
 *
 * @param[in,out] deque Pointer to the deque structure to be initialized.
 */
void deque_init(deque_t *deque);

/**
 * @brief Frees the memory used by the deque.
 *
 * @param[in,out] deque Pointer to the deque structure to be freed.
 */
void deque_free(deque_t *deque);

/**
 * @brief Retrieves the element at the specified index in the deque.
 *
 * @param[in] deque Pointer to the deque structure.
 * @param[in] index Index of the element to retrieve.
 * @return Pointer to the element at the specified index, or NULL if the index is out of bounds.
 */
tile_t *deque_at(const deque_t *deque, size_t index);

/**
 * @brief Pushes an element to the front of the deque.
 *
 * If the deque is full, it is resized to accommodate more elements.
 *
 * @param[in,out] deque Pointer to the deque structure.
 * @param[in] tile Element to be pushed to the front of the deque.
 */
void deque_push_front(deque_t *deque, tile_t tile);

/**
 * @brief Pushes an element to the rear of the deque.
 *
 * If the deque is full, it is resized to accommodate more elements.
 *
 * @param[in,out] deque Pointer to the deque structure.
 * @param[in] tile Element to be pushed to the rear of the deque.
 */
void deque_push_rear(deque_t *deque, tile_t tile);

/**
 * @brief Pops the element from the front of the deque.
 *
 * If the deque becomes too empty, it is resized to conserve memory.
 *
 * @param[in,out] deque Pointer to the deque structure.
 */
void deque_pop_front(deque_t *deque);

/**
 * @brief Pops the element from the rear of the deque.
 *
 * If the deque becomes too empty, it is resized to conserve memory.
 *
 * @param[in,out] deque Pointer to the deque structure.
 */
void deque_pop_rear(deque_t *deque);

