#pragma once

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define ZERO(x) memset((char *)&x, 0, sizeof(x))

static inline void ERROR(char *x) {
    dprintf(1, "Error: %s\n", x);
    exit(EXIT_FAILURE);
}
