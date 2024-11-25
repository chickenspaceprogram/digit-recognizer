#ifndef NET_H
#define NET_H

#include "blas_wrapper.h"
#include <stdlib.h>
#include <stdbool.h>
#include "rand.h"

typedef struct layer {
    const int size;
    bool malloc_error;
    float *weights;
    float *biases;
    float *activations;
    float *activations_no_fn;
    void (*free)(Layer *);
    // first Layer *: current layer
    // second Layer *: last layer
    // double (*)(double *): pointer to activation function
    void (*set_activations)(Layer *, Layer *, double (*)(double *));
} Layer;

Layer newLayer(int size, int prev_size);

#endif