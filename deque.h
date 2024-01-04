/**
 * @file
 * @brief File that contains the definitions of a double ended queue.
 */
#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>
#include "card.h"

/**
 * @brief A double ended queue implemented using a circular array.
 */
typedef struct {
    size_t length; /**< The current number of elements contained in the double ended queue. */
    size_t capacity; /**< Maximum capacity of the double ended queue. */
    card_t *array; /**< A pointer to an array containing the data of the double ended queue. */
    card_t *front; /**< A pointer to the front of the double ended queue. */
    card_t *rear; /**< A pointer to the rear of the double ended queue. */
} deque_t;

/**
 * @brief Function used to initialize a double ended queue.
 *
 * @param deque the double ended queue to initialize.
 * @param capacity the maximum capacity of the double ended queue.
 */
void deque_init(deque_t *deque, size_t capacity);

/**
 * @brief Function used to free a double ended queue.
 *
 * @param deque the double ended queue to free.
 */
void deque_free(deque_t *deque);

/**
 * @brief Function that returns a pointer to the element at the index passed as a parameter.
 *
 * @param deque the double ended queue that contains the element.
 * @param index the position of the element in the double ended queue.
 * @return A pointer to the element at index or a NULL pointer if the index is out of bounds.
 */
card_t *deque_at(deque_t *deque, size_t index);

/**
 * @brief Function that pushes an element to the front of the double ended queue.
 *
 * @param deque the double ended queue.
 * @param value the value to push.
 */
void deque_push_front(deque_t *deque, card_t value);

/**
 * @brief Function that pushes an element to the rear of the double ended queue.
 *
 * @param deque the double ended queue.
 * @param value the value to push.
 */
void deque_push_rear(deque_t *deque, card_t value);

#endif // DEQUE_H
