#ifndef ACTIVATION_FUNCS_H
#define ACTIVATION_FUNCS_H

#include <math.h>

#define LEAKY_RELU_ALPHA 0.01
#define ELU_ALPHA 1

float ReLU(float val);
float ReLU_deriv(float val);

float sigmoid(float val);
float sigmoid_deriv(float val);

float ELU(float val);
float ELU_deriv(float val);

float leaky_ReLU(float val);
float leaky_ReLU_deriv(float val);

#endif