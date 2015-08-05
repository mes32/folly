/**
 *  randfolly.h - folly
 *
 *  This module defines ...
 *
 */

#ifndef RANDFOLLY_H_
#define RANDFOLLY_H_


/**
 *  Initializes randomization with the provided random seed
 */
void initRandomSeed(unsigned seed);

/**
 *  Produces a random int with a uniform distribution ranging from min to max
 */
int randUnif(int min, int max);


#endif // RANDFOLLY_H_
