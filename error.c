#include <stdlib.h>
#include <stdio.h>
#include "error.h"

void die(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

