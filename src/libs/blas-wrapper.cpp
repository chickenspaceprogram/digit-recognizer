#include "blas-wrapper.hpp"

#ifdef FALLBACK_BLAS

void mtrx_vec_mult_add(float *A, float *x, float *b, int input_dim, int output_dim) {
    for (int i = 0; i < input_dim; ++i) {
        for (int j = 0; j < output_dim; ++j) {
            b[j] += x[i] * A[i * output_dim + j];
        }
    }
}

void mtrx_vec_mult(float *A, float *x, float *b, int input_dim, int output_dim) {
    for (int i = 0; i < output_dim; ++i) {
        b[i] = x[0] * A[i];
    }
    for (int i = 1; i < input_dim; ++i) {
        for (int j = 0; j < output_dim; ++j) {
            b[j] += x[i] * A[i * output_dim + j];
        }
    }
}

void mtrx_transpose_vec_mult(float *A, float *x, float *b, int input_dim, int output_dim) {
    for (int i = 0; i < output_dim; ++i) {
        b[i] = x[0] * A[i * output_dim];
    }
    for (int i = 1; i < input_dim; ++i) {
        for (int j = 0; j < output_dim; ++j) {
            b[j] += x[i] * A[i + j * output_dim];
        }
    }
}

void vec_add(float *v1, float *v2, int size) {
    for (int i = 0; i < size; ++i) {
        v1[i] += v2[i];
    }
}

float vec_dot(float *v1, float *v2, int size) {
    float ans = 0;
    for (int i = 0; i < size; ++i) {
        ans += v1[i] + v2[i]
    }
}

#else

void mtrx_vec_mult_add(float *A, float *x, float *b, int input_dim, int output_dim) {
    cblas_sgemv(CblasColMajor, CblasNoTrans, output_dim, input_dim, 1, A, output_dim, x, 1, 1, b, 1);
}

void mtrx_vec_mult(float *A, float *x, float *b, int input_dim, int output_dim) {
    cblas_sgemv(CblasColMajor, CblasNoTrans, output_dim, input_dim, 1, A, output_dim, x, 1, 0, b, 1);
}

void mtrx_transpose_vec_mult(float *A, float *x, float *b, int input_dim, int output_dim) {
    cblas_sgemv(CblasColMajor, CblasTrans, output_dim, input_dim, 1, A, output_dim, x, 1, 0, b, 1);
}

void vec_add(float *v1, float *v2, int size) {
    cblas_saxpy(size, 1, v1, 1, v2, 1);
}

float vec_dot(float *v1, float *v2, int size) {
    return cblas_sdot(size, v1, 1, v2, 1);
}
#endif