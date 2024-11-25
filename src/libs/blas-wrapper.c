#include "blas-wrapper.h"

void mtrx_vec_mult(float *A, float *x, float *b, int input_dim, int output_dim) {
    cblas_sgemv(CblasColMajor, CblasNoTrans, output_dim, input_dim, 1, A, output_dim, x, 1, 0, b, 1);
}

void vec_add(float *v1, float *v2, int size) {
    cblas_saxpy(size, 1, v1, 1, v2, 1);
}