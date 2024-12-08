#include "activation-funcs.hpp"
#include <assert.h>


float ReLU::Function(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val > 0) {
        return val;
    }
    return (float)0;
}
float ReLU::Derivative(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val > 0) {
        return (float)1;
    }
    return (float)0;
}

float Sigmoid::Function(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    assert(!isinf(1 / (expf(-val) + 1)));
    assert(!isnan(1 / (expf(-val) + 1)));
    return 1 / (expf(-val) + 1);
}
float Sigmoid::Derivative(float val) {
    float sig = Sigmoid::Function(val);
    assert(!isinf(val));
    assert(!isnan(val));
    assert(!isinf(sig));
    assert(!isnan(sig));
    return sig * (1 - sig);
}

float ELU::Function(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val >= 0) {
        return val;
    }
    assert(!isinf(ELU_ALPHA * (expf(val) - 1)));
    assert(!isnan(ELU_ALPHA * (expf(val) - 1)));
    return ELU_ALPHA * (expf(val) - 1);
}
float ELU::Derivative(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val >= 0) {
        return 1;
    }
    assert(!isinf(ELU_ALPHA * expf(val)));
    assert(!isnan(ELU_ALPHA * expf(val)));
    return ELU_ALPHA * expf(val);
}

float LeakyReLU::Function(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val >= 0) {
        return val;
    }
    return LEAKY_RELU_ALPHA * val;
}
float LeakyReLU::Derivative(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val > 0) {
        return 1;
    }
    return LEAKY_RELU_ALPHA;
}

float ReLU6::Function(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val <= 0) {
        return 0;
    }
    else if (val >= 6) {
        return 6;
    }
    return val;
}
float ReLU6::Derivative(float val) {
    assert(!isinf(val));
    assert(!isnan(val));
    if (val > 0 || val < 6) {
        return 1;
    }
    return 0;
}