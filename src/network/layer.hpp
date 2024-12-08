#ifndef LAYER_HPP
#define LAYER_HPP

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
        void CalcError(Layer &last_layer, ActivationFunction& fn);
        std::vector<float> GetWeightsDeriv(Layer &last);
        std::vector<float> GetBiasesDeriv(void);
        int GetSize() const;
        // yeah i know public fields suck
        std::vector<float> weights;
        std::vector<float> biases;
        std::vector<float> activations;
        std::vector<float> error;

    private:
        int size;
        int prev_size;
        std::vector<float> activations_no_fn;
};

#endif