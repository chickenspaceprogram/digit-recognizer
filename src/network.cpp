#include "network.hpp"

Network::Network(int input_len, int hidden_len, int output_len, int num_hidden_layers, int gradient_mult) : 
    input_len(input_len), 
    hidden_len(hidden_len),
    output_len(output_len), 
    num_hidden_layers(num_hidden_layers),
    gradient_mult(gradient_mult),
    start(input_len, input_len),
    end(output_len, hidden_len) {

        Layer first(hidden_len, input_len);
        this->hidden.push_back(first);

        for (int i = 1; i < (num_hidden_layers); ++i) {
            Layer layer(hidden_len, hidden_len);
            this->hidden.push_back(layer);
        }
}

void Network::Zero() {
    start.Zero();
    end.Zero();
    for (int i = 0; i < hidden.size(); ++i) {
        hidden[i].Zero();
    }
}