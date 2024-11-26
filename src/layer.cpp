#include "layer.hpp"


Layer::Layer(int size, int previous_size) : 
    size(size)
{
    for (int i = 0; i < size * previous_size; ++i) {
        weights.push_back(rand_weight());
    }
    for (int i = 0; i < previous_size; ++i) {
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

void Layer::BackProp(Layer &next_layer, ActivationFunction& fn) {
    FindBiasDeriv(fn);
    mtrx_transpose_vec_mult(&(next_layer.weights[0]), &(next_layer.activations_deriv[0]), &(activations_deriv[0]), next_layer.activations_deriv.size(), activations_deriv.size());
    for (int i = 0; i < activations_deriv.size(); ++i) {
        activations_deriv[i] *= biases_deriv[i]; // biases_deriv_j is equal to phi'(net_j)
    }
    
}

void Layer::FindBiasDeriv(ActivationFunction& fn) {
    for (int i = 0; i < size; ++i) {
        biases_deriv[i] = fn.Derivative(activations_no_fn[i]);
    }
}