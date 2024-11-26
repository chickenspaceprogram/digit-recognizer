#ifndef ACTIVATION_FUNCS_HPP
#define ACTIVATION_FUNCS_HPP

#include <math.h>

#define LEAKY_RELU_ALPHA 0.01
#define ELU_ALPHA 1

enum ActivationFnType {
    ReLU,
    Sigmoid,
    ELU,
    LeakyReLU,
};

struct ActivationFunction {
    virtual float Function(float input) = 0;
    virtual float Derivative(float input) = 0;
};

class ReLU : ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

class Sigmoid : ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

class ELU : ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

class LeakyReLU : ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

#endif