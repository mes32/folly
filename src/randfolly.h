/**
 *  randfolly.h - folly
 *
 *  This module defines pseudorandom number generation for randomizing game behavior
 *
 */

#ifndef RANDFOLLY_H_
#define RANDFOLLY_H_


/**
 * Initializes randomization with the provided random seed
 */
void initRandomSeed(unsigned seed);

/**
 * Produces a random double with a uniform distribution normalized to the range [0, 1)
 */
double normalizedRand();

/**
 * Produces a random int with a uniform distribution ranging from min to max
 */
int randUnif(int min, int max);


#endif // RANDFOLLY_H_
