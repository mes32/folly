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
void initRandomSeed(unsigned seed) {
    srand(seed);
}

/**
 *  Produces a random double with a uniform distribution normalized to the range [0, 1)
 */
double normalizedRand() {
    double p = (double)rand();
    double q = ((double)RAND_MAX) + 1.0;
    return p/q;
}

/**
 *  Produces a random int with a uniform distribution ranging from min to max
 */
int randUnif(int min, int max) {
    double range = (double)(max - min + 1);
    return (normalizedRand() * range) + min;
}
