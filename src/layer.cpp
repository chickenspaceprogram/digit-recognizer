#include "layer.hpp"


Layer::Layer(int size, int previous_size) : 
    size(size),
    prev_size(previous_size)
{
    for (int i = 0; i < size * previous_size; ++i) {
        weights.push_back(rand_weight());
        weights_deriv.push_back((float)0);
    }
    for (int i = 0; i < size; ++i) {
        biases.push_back((float)0);
        biases_deriv.push_back((float)0);
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
    }
}

void Layer::CalcGradients(Layer &last_layer, ActivationFunction &fn) {
    float temp;
    for (int j = 0; j < size; ++j) {
        biases_deriv[j] = fn.Derivative(activations_no_fn[j]) * activations_deriv[j];
        for (int k = 0; k < last_layer.GetSize(); ++k) {
            weights_deriv[j + k * size] = biases_deriv[j] * last_layer.activations[k];
        }
    }
    for (int k = 0; k < last_layer.GetSize(); ++k) {
        temp = 0;
        for (int j = 0; j < size; ++j) {
            temp += biases_deriv[j] * weights_deriv[j + k * size];
        }
        last_layer.activations_deriv[k] = temp;
    }
}

void Layer::Zero() {
    for (int j = 0; j < size; ++j) {
        biases_deriv[j] = 0;
        activations_deriv[j] = 0;
        for (int k = 0; k < size; ++k) {
            weights_deriv[j + k * size] = 0;
        }
    }
}