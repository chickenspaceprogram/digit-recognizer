#ifndef BLAS_WRAPPER_H
#define BLAS_WRAPPER_H
#include <cblas.h>

// computes Ax and stores the result in b
// assumes A is in column-major order
void mtrx_vec_mult(float *A, float *x, float *b, int input_dim, int output_dim);

// stores v1 + v2 in v2
void vec_add(float *v1, float *v2, int size);

#endif