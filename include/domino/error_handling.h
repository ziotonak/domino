/**
 * @file error_handling.h
 * @brief Implementation of error handling functions.
 */

#pragma once

/**
 * @brief Prints an error message, including system-specific error description,
 *        and exits the program with a failure status.
 *
 * @param[in] message - The error message to be printed.
 */
void die(const char *message);

