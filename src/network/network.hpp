#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "layer.hpp"

class Network {
    public:
        Network(int input_len, int hidden_len, int output_len, int num_hidden_layers, int gradient_mult);
        void Zero();
    private:
        int input_len;
        int hidden_len;
        int output_len;
        int num_hidden_layers;
        int gradient_mult;
        std::vector<Layer> hidden;
        Layer start;
        Layer end;
};

#endif