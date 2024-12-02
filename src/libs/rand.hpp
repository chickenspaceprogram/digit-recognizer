#ifndef RAND_HPP
#define RAND_HPP

#include <stdlib.h>
#include <time.h>

void seed_rand(void);
float rand_weight(float activation_multiplier);
int randint(int min, int max); // min <= returned value < max


#endif