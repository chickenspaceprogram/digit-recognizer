#include "layer.hpp"


Layer::Layer(int size, int previous_size, float activation_multiplier) : 
    size(size),
    prev_size(previous_size)
{
    weights.reserve(size * previous_size);
    weights_deriv.reserve(size * previous_size);
    biases.reserve(size);
    activations.reserve(size);
    activations_deriv.reserve(size);
    activations_no_fn.reserve(size);
    
    for (int i = 0; i < size * previous_size; ++i) {
        weights.push_back(rand_weight(activation_multiplier));
        weights_deriv.push_back((float)0);
    }
    for (int i = 0; i < size; ++i) {
        biases.push_back((float)0);
        activations.push_back((float)0);
        activations_deriv.push_back((float)0);
        activations_no_fn.push_back((float)0);
    }
}

int Layer::GetSize() const {
    return size;
}

void Layer::SetActivations(Layer& prev_layer, ActivationFunction& fn) {
    mtrx_vec_mult(&weights[0], &(prev_layer.activations[0]), &activations_no_fn[0], prev_layer.GetSize(), size);
    vec_add(&biases[0], &activations_no_fn[0], size);
    for (int i = 0; i < size; ++i) {
        activations[i] = fn.Function(activations_no_fn[i]);
        if (isnan(activations[i])) {
            printf("what the sigma");
            exit(3232);
        }
    }
}

void Layer::CalcGradients(Layer &last_layer, ActivationFunction &fn) {
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < last_layer.GetSize(); ++k) {
            weights_deriv[j + k * size] = activations_deriv[j] * last_layer.activations[k];
        }
    }
    mtrx_transpose_vec_mult(&(weights[0]), &(activations_deriv[0]), &(last_layer.activations_deriv[0]), activations_deriv.size(), last_layer.activations_deriv.size());
    for (int k = 0; k < last_layer.GetSize(); ++k) {
        last_layer.activations_deriv[k] *= fn.Derivative(last_layer.activations_no_fn[k]);
    }
}

void Layer::Zero() {
    for (int j = 0; j < size; ++j) {
        activations_deriv[j] = 0;
        for (int k = 0; k < size; ++k) {
            weights_deriv[j + k * size] = 0;
        }
    }
}