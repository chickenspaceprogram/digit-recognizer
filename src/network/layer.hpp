#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include <stdbool.h>
#include "../libs/blas-wrapper.hpp"
#include "../libs/rand.hpp"
#include "activation-funcs.hpp"

class Layer {
    public:
        Layer(int size, int previous_size);
        void SetActivations(Layer& prev_layer, ActivationFunction& fn);
        void CalcGradients(Layer &last_layer, ActivationFunction& fn);
        void Zero();
        int GetSize() const;
        std::vector<float> weights;
        std::vector<float> weights_deriv;

        std::vector<float> biases;
        std::vector<float> biases_deriv;

        std::vector<float> activations;
        std::vector<float> activations_deriv;

    private:
        const int size;
        const int prev_size;
        std::vector<float> activations_no_fn;
};

#endif