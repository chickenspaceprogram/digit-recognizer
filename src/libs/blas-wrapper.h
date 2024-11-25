#ifndef BLAS_WRAPPER_H
#define BLAS_WRAPPER_H
#if defined(__APPLE__) && defined(__MACH__)
#include <Accelerate/Accelerate.h>
#elif defined(_WIN32)
#else
#include <openblas/cblas.h>
#endif

// adds the result of Ax to what is already stored in b
void mtrx_vec_mult_add(float *A, float *x, float *b, int input_dim, int output_dim);

// computes Ax and stores the result in b
// assumes A is in column-major order
void mtrx_vec_mult(float *A, float *x, float *b, int input_dim, int output_dim);

// stores v1 + v2 in v2
void vec_add(float *v1, float *v2, int size);

#endif