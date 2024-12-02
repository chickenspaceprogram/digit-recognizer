#include "rand.hpp"
#include <stdio.h>

void seed_rand(void) {
	srand((unsigned int) time(NULL));
}

float rand_weight(float activation_multiplier) {
    float weight = (float)rand() / RAND_MAX;
    return ((weight * 2) - 1) * activation_multiplier;
}

int randint(int min, int max) {
    int diff = max - min;
    return rand() % diff + min;
}