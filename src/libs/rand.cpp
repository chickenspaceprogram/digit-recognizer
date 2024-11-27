#include "rand.hpp"
#include <stdio.h>

void seed_rand(void) {
	srand((unsigned int) time(NULL));
}

float rand_weight(void) {
    float weight = (float)rand() / RAND_MAX;
    return ((weight * 2) - 1);
}

int randint(int min, int max) {
    int diff = max - min;
    return rand() % diff + min;
}