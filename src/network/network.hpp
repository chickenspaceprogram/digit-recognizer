#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "layer.hpp"
#include <vector>

struct LayerDerivatives {
    void operator+=(LayerDerivatives const &derivs);
    static LayerDerivatives GetLayerDerivatives(Layer &layer);
    void SetLayerDerivatives(Layer &layer, float multiplier);
    std::vector<float> bias;
    std::vector<float> weight;
};

struct Derivatives {
    void operator+=(Derivatives const &derivs);
    std::vector<LayerDerivatives> hidden;
    LayerDerivatives input;
    LayerDerivatives output;
};

class Network {
    public:
        Network() = delete;
        Network(int input_len, int hidden_len, int output_len, int num_hidden_layers, float gradient_mult);
        void Zero();
        int GetNumHidden();
        int GetHiddenLen();
        int GetInputLen();
        int GetOutputLen();
        float GetGradientMult();
        void SetInput(std::vector<float> inputs);
        void SetOutputDeriv(std::vector<float> outputs);
        std::vector<float> &GetOutput();
        void RunNetwork(ActivationFunction &fn, ActivationFunction &end_actfn);
        void BackProp(ActivationFunction &fn, ActivationFunction &end_actfn);
        Derivatives GetCurrentDerivatives();
        void AddDerivatives(Derivatives &derivs);
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