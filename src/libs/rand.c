#include "rand.h"

void seed_rand(void) {
	srand((unsigned int) time(NULL));
}

double rand_weight(void) {
    double weight = (double)rand() / RAND_MAX;
    return (weight * 2) - 1;
}