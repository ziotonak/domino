#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void die(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

