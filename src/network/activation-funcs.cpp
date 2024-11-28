#include "activation-funcs.hpp"


float ReLU::Function(float val) {
    if (val > 0) {
        return val;
    }
    return 0;
}
float ReLU::Derivative(float val) {
    if (val > 0) {
        return 1;
    }
    return 0;
}

float Sigmoid::Function(float val) {
    return 1 / (expf(-val) + 1);
}
float Sigmoid::Derivative(float val) {
    float sig = Sigmoid::Function(val);
    return sig * (1 - sig);
}

float ELU::Function(float val) {
    if (val >= 0) {
        return val;
    }
    return ELU_ALPHA * (expf(val) - 1);
}
float ELU::Derivative(float val) {
    if (val >= 0) {
        return 1;
    }
    return ELU_ALPHA * expf(val);
}

float LeakyReLU::Function(float val) {
    if (val >= 0) {
        return val;
    }
    return LEAKY_RELU_ALPHA * val;
}
float LeakyReLU::Derivative(float val) {
    if (val > 0) {
        return 1;
    }
    return LEAKY_RELU_ALPHA;
}

float ReLU6::Function(float val) {
    if (val <= 0) {
        return 0;
    }
    else if (val >= 6) {
        return 6;
    }
    return val;
}
float ReLU6::Derivative(float val) {
    if (val > 0 || val < 6) {
        return 1;
    }
    return 0;
}