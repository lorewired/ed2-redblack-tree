#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define to_int32(e) (*((int32_t *) e))
#define to_int64(e) (*((int64_t *) e))

#define to_float(e) (*((float *) e))
#define to_double(e) (*((double *) e))

#define to_str(e) (*((char *) e))

#define swap(a, b) do { \
    (a) ^= (b);         \
    (b) ^= (a);         \
    (a) ^= (b);         \
} while (0)

#endif