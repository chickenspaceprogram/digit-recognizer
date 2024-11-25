// testing for compile errors
#include "layer.hpp"
#include "activation-funcs.hpp"

#include "libs/rand.hpp"
#include "libs/load-img.hpp"
#include "libs/blas-wrapper.hpp"



#include <stdio.h>

int main(void) {
    seed_rand();
    printf("Hello world\n");
}