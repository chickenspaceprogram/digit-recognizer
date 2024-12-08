#include "../blas-wrapper.hpp"

#include <assert.h>

void mtrx_vec_mult_test(void) {
    float A[] = {1, 2, 3, 4, 5, 6}; // [1, 2; 3, 4; 5, 6]
    float x[] = {7, 8}; // [7; 8]
    float b[3];

    mtrx_vec_mult(A, x, b, 2, 3);
    
    assert(b[0] == 23);
    assert(b[1] == 53);
    assert(b[2] == 83);
}

void mtrx_vec_mult_add_test(void) {
    float A[] = {1, 2, 3, 4, 5, 6}; // [1, 2; 3, 4; 5, 6]
    float x[] = {7, 8}; // [7; 8]
    float b[] = {9, 10, 11};

    mtrx_vec_mult_add(A, x, b, 2, 3);

    assert(b[0] == 32);
    assert(b[1] == 63);
    assert(b[2] == 94);
}

void mtrx_transpose_vec_mult_test(void) {
    float A[] = {1, 2, 3, 4, 5, 6}; // [1, 2, 3; 4, 5, 6]
    float x[] = {7, 8}; // [7; 8]
    float b[3];

    mtrx_transpose_vec_mult(A, x, b, 2, 3);

    assert(b[0] == 39);
    assert(b[1] == 54);
    assert(b[2] == 69);
}

void vec_add_test(void) {
    float v1[] = {1, 2, 3, 4, 5};
    float v2[] = {6, 7, 8, 9, 10};
    float v2_perm[] = {6, 7, 8, 9, 10};

    vec_add(v1, v2, 5);
    for (int i = 0; i < 5; ++i) {
        assert(v2[i] == v2_perm[i] + v1[i]);
    }
}

void vec_dot_test(void) {
    float v1[] = {1, 2, 3, 4, 5};
    float v2[] = {6, 7, 8, 9, 10};
    assert(vec_dot(v1, v2, 5) == 130);
}

void vec_cpy_test(void) {
    float v1[] = {123, 456, 789, 987, 654, 321};
    float v2[6];
    vec_cpy(v1, v2, 6);
    for (int i = 0; i < 6; ++i) {
        assert(v1[i] == v2[i]);
    }
}

int main(void) {
    mtrx_vec_mult_test();
    mtrx_vec_mult_add_test();
    mtrx_transpose_vec_mult_test();
    vec_add_test();
    vec_dot_test();
    vec_cpy_test();
}