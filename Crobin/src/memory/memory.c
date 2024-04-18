//
// Created by icelake on 24-4-18.
//

#include <stdio.h>
#include "memory.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL) {
        perror("Failed to allocate memory for instruction sequence.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
