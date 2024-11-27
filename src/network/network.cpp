#include "network.hpp"

Network::Network(Network &network) {
    input_len = network.GetInputLen();
    hidden_len = network.GetHiddenLen();
    output_len = network.GetOutputLen();
    num_hidden_layers = network.GetNumHidden();
    gradient_mult = network.GetGradientMult();
    start = network.start;
    end = network.end;
    Zero();
}

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

int Network::GetNumHidden() {
    return num_hidden_layers;
}
int Network::GetHiddenLen() {
    return hidden_len;
}
int Network::GetInputLen() {
    return input_len;
}
int Network::GetOutputLen() {
    return output_len;
}

float Network::GetGradientMult() {
    return gradient_mult;
}

void Network::SetInput(std::vector<float> inputs) {
    start.activations = inputs;
}
void Network::SetOutputDeriv(std::vector<float> outputs) {
    end.activations_deriv = outputs;
}
std::vector<float> &Network::GetOutput() {
    return end.activations;
}

void Network::RunNetwork(ActivationFunction &fn) {
    hidden[0].SetActivations(start, fn);
    for (int i = 1; i < hidden.size(); ++i) {
        hidden[i].SetActivations(hidden[i - 1], fn);
    }
    end.SetActivations(hidden[hidden.size() - 1], fn);
}

void Network::BackProp(ActivationFunction &fn) {
    end.CalcGradients(hidden[hidden.size() - 1], fn);
    for (int i = hidden.size() - 1; i >= 0; --i) {
        hidden[i].CalcGradients(hidden[i - 1], fn);
    }
    start.CalcGradients(hidden[0], fn);
}

Derivatives Network::GetCurrentDerivatives() {
    Derivatives derivs;
    derivs.input = LayerDerivatives::GetLayerDerivatives(start);
    derivs.output = LayerDerivatives::GetLayerDerivatives(end);
    for (int i = 0; i < num_hidden_layers; ++i) {
        //derivs.hidden.push_back();
    }
}

LayerDerivatives LayerDerivatives::GetLayerDerivatives(const Layer &layer) {
    LayerDerivatives lderivs;
    lderivs.bias = layer.biases_deriv;
    lderivs.weight = layer.weights_deriv;
    return lderivs;
}