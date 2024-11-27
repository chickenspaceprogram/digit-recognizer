#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "layer.hpp"
#include <vector>

struct LayerDerivatives {
    void operator+=(const LayerDerivatives &derivs);
    static LayerDerivatives GetLayerDerivatives(const Layer &layer);
    std::vector<float> bias;
    std::vector<float> weight;
};

struct Derivatives {
    void operator+=(const Derivatives &derivs);
    std::vector<LayerDerivatives> hidden;
    LayerDerivatives input;
    LayerDerivatives output;
};

class Network {
    public:
        Network(int input_len, int hidden_len, int output_len, int num_hidden_layers, int gradient_mult);
        void Zero();
        int GetNumHidden();
        int GetHiddenLen();
        int GetInputLen();
        int GetOutputLen();
        float GetGradientMult();
        void SetInput(std::vector<float> inputs);
        void SetOutputDeriv(std::vector<float> outputs);
        std::vector<float> &GetOutput();
        void RunNetwork(ActivationFunction &fn);
        void BackProp(ActivationFunction &fn);
        Derivatives GetCurrentDerivatives();
    private:
        int input_len;
        int hidden_len;
        int output_len;
        int num_hidden_layers;
        float gradient_mult;
        std::vector<Layer> hidden;
        Layer start;
        Layer end;
};

#endif