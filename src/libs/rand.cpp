#include "rand.hpp"

void seed_rand(void) {
	srand((unsigned int) time(NULL));
}

float rand_weight(void) {
    float weight = (float)rand() / RAND_MAX;
    return (weight * 2) - 1;
}