#include "layer.hpp"


Layer::Layer(int size, int previous_size, float activation_multiplier) : 
    size(size),
    prev_size(previous_size)
{
    weights.reserve(size * previous_size);
    biases.reserve(size);
    activations.reserve(size);
    error.reserve(size);
    activations_no_fn.reserve(size);
    
    for (int i = 0; i < size * previous_size; ++i) {
        weights.push_back(rand_weight(activation_multiplier));
    }
    for (int i = 0; i < size; ++i) {
        biases.push_back((float)0);
        activations.push_back((float)0);
        error.push_back((float)0);
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

void Layer::CalcError(Layer &last_layer, ActivationFunction &fn) {
    mtrx_transpose_vec_mult(&(weights[0]), &(error[0]), &(last_layer.error[0]), error.size(), last_layer.error.size());
    for (int k = 0; k < last_layer.GetSize(); ++k) {
        last_layer.error[k] *= fn.Derivative(last_layer.activations_no_fn[k]);
    }
}

std::vector<float> Layer::GetWeightsDeriv(Layer &last) {
    std::vector<float> out;
    for (int k = 0; k < last.GetSize(); ++k) {
        for (int j = 0; j < size; ++j) {
            out.push_back(last.activations[k] * error[j]);
        }
    }
    return out;
}

std::vector<float> Layer::GetBiasesDeriv(void) {

    return error;
}