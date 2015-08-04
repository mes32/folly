/**
 *  randfolly.c - folly
 *
 *  This module defines ...
 *
 */

#include <stdlib.h>
#include "randfolly.h"


/**
 *  Initializes randomization with the provided random seed
 */
void initRandomSeed(int seed) {
    srand(seed);
}
