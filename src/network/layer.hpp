#ifndef NET_HPP
#define NET_HPP

#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include "../libs/blas-wrapper.hpp"
#include "../libs/rand.hpp"
#include "activation-funcs.hpp"

class Layer {
    public:
        Layer(int size, int previous_size, float activation_multiplier);
        void SetActivations(Layer& prev_layer, ActivationFunction& fn);
        void CalcGradients(Layer &last_layer, ActivationFunction& fn);
        void Zero();
        int GetSize() const;
        std::vector<float> weights;
        std::vector<float> weights_deriv;

        std::vector<float> biases;

        std::vector<float> activations;
        std::vector<float> activations_deriv;

    private:
        int size;
        int prev_size;
        std::vector<float> activations_no_fn;
};

#endif