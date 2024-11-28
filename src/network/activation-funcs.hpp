#ifndef ACTIVATION_FUNCS_HPP
#define ACTIVATION_FUNCS_HPP

#include <math.h>

#define LEAKY_RELU_ALPHA 0.01
#define ELU_ALPHA 1

struct ActivationFunction {
    virtual float Function(float input) = 0;
    virtual float Derivative(float input) = 0;
};

class ReLU : public ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

class Sigmoid : public ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

class ELU : public ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

class LeakyReLU : public ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

class ReLU6 : public ActivationFunction {
    virtual float Function(float input);
    virtual float Derivative(float input);
};

#endif