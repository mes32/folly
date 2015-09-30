/**
 *  randfolly.c - folly
 *
 *  This module defines pseudorandom number generation for randomizing game behavior
 *
 */

#include <stdarg.h>
#include <stdlib.h>

#include "debugfolly.h"
#include "randfolly.h"


//static int randIntFromSet(int in1, ...);

/**
 * Initializes randomization with the provided random seed
 */
void initRandomSeed(unsigned seed) {
    srand(seed);
}

/**
 * Produces a random double with a uniform distribution normalized to the range [0, 1)
 */
double normalizedRand() {
    double p = (double)rand();
    double q = ((double)RAND_MAX) + 1.0;
    return p/q;
}

/**
 * Produces a random int with a uniform distribution ranging from min to max
 */
int randUnif(int min, int max) {
    double range = (double)(max - min + 1);
    return (normalizedRand() * range) + min;
}

/**
 * Selects one int at random from an arbitrarily sized list of ints
 */
int randIntFromList(size_t numArgs, ...) {
    int targetIndex = randUnif(0, numArgs-1);

    va_list ap;
    va_start (ap, numArgs);

    int arg;
    for (int i=0; i <= targetIndex && i < numArgs; i++) {
        arg = va_arg(ap, int);
    }
    va_end (ap);

    return arg;
}
