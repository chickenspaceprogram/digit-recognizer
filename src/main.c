// testing for compile errors
#include "layer.h"
#include "activation-funcs.h"

#include "libs/rand.h"
#include "libs/load-img.h"
#include "libs/blas-wrapper.h"



#include <stdio.h>

int main(void) {
    seed_rand();
    printf("Hello world\n");
}