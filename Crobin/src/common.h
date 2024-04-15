//
// Created by icelake on 24-4-14.
//

#ifndef CROBIN_COMMON_H
#define CROBIN_COMMON_H

#define DEBUG_TRACE_EXECUTION


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stdlib.h"

#define NEW(type, size) (type *)malloc(sizeof(type) * (size))

#endif //CROBIN_COMMON_H