#include <stdlib.h>
#include <stdio.h>
#include <domino/error_handling.h>

void die(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

