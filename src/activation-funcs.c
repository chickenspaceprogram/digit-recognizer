#include "activation-funcs.h"

float ReLU(float val) {
    if (val > 0) {
        return val;
    }
    return 0;
}
float ReLU_deriv(float val) {
    if (val > 0) {
        return 1;
    }
    return 0;
}

float sigmoid(float val) {
    return 1 / (expf(-val) + 1);
}
float sigmoid_deriv(float val) {
    float sig = sigmoid(val);
    return sig * (1 - sig);
}

float ELU(float val) {
    if (val >= 0) {
        return val;
    }
    return ELU_ALPHA * (exp(val) - 1);
}
float ELU_deriv(float val) {
    if (val >= 0) {
        return 1;
    }
    return ELU_ALPHA * exp(val);
}

float leaky_ReLU(float val) {
    if (val >= 0) {
        return val;
    }
    return LEAKY_RELU_ALPHA * val
}
float leaky_ReLU_deriv(float val) {
    if (val > 0) {
        return 1;
    }
    return LEAKY_RELU_ALPHA;
}