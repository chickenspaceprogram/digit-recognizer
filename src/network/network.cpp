#include "network.hpp"

Network::Network(int input_len, int hidden_len, int output_len, int num_hidden_layers, float gradient_mult, float activation_multiplier) : 
input_len(input_len), 
hidden_len(hidden_len),
output_len(output_len), 
num_hidden_layers(num_hidden_layers),
gradient_mult(gradient_mult),
start(input_len, input_len, activation_multiplier),
end(output_len, hidden_len, activation_multiplier) {

    Layer first(hidden_len, input_len, activation_multiplier);
    this->hidden.push_back(first);

    for (int i = 1; i < (num_hidden_layers); ++i) {
        Layer layer(hidden_len, hidden_len, activation_multiplier);
        this->hidden.push_back(layer);
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
    end.error = outputs;
}

std::vector<float> &Network::GetOutput() {
    return end.activations;
}

void Network::RunNetwork(ActivationFunction &fn, ActivationFunction &end_actfn) {
    hidden[0].SetActivations(start, fn);
    for (unsigned int i = 1; i < hidden.size(); ++i) {
        hidden[i].SetActivations(hidden[i - 1], fn);
    }
    end.SetActivations(hidden[hidden.size() - 1], end_actfn);
}

void Network::BackProp(ActivationFunction &fn, ActivationFunction &end_actfn) {
    end.CalcError(hidden[hidden.size() - 1], end_actfn);
    for (int i = hidden.size() - 1; i > 0; --i) {
        hidden[i].CalcError(hidden[i - 1], fn);
    }
    hidden[0].CalcError(start, fn);
}

Derivatives Network::GetCurrentDerivatives() {
    Derivatives derivs;
    derivs.output = LayerDerivatives::GetLayerDerivatives(end, hidden[num_hidden_layers - 1]);
    derivs.hidden.push_back(LayerDerivatives::GetLayerDerivatives(hidden[0], start));
    for (int i = 1; i < num_hidden_layers; ++i) {
        derivs.hidden.push_back(LayerDerivatives::GetLayerDerivatives(hidden[i], hidden[i - 1]));
    }
    return derivs;
}

void Network::AddDerivatives(Derivatives &derivs) {
    derivs.output.SetLayerDerivatives(end, gradient_mult);
    for (int i = 0; i < num_hidden_layers; ++i) {
        derivs.hidden[i].SetLayerDerivatives(hidden[i], gradient_mult);
    }
}

void LayerDerivatives::operator+=(LayerDerivatives const &derivs) {
    for (unsigned int i = 0; i < derivs.bias.size(); ++i) {
        bias[i] += derivs.bias[i];
    }
    for (unsigned int i = 0; i < derivs.weight.size(); ++i) {
        weight[i] += derivs.weight[i];
    }
}

void Derivatives::operator+=(Derivatives const &derivs) {
    output += derivs.output;
    for (unsigned int i = 0; i < hidden.size(); ++i) {
        hidden[i] += derivs.hidden[i];
    }
}

LayerDerivatives LayerDerivatives::GetLayerDerivatives(Layer &layer, Layer &last_layer) {
    LayerDerivatives lderivs;
    lderivs.bias = layer.GetBiasesDeriv();
    lderivs.weight = layer.GetWeightsDeriv(last_layer);
    return lderivs;
}

void LayerDerivatives::SetLayerDerivatives(Layer &layer, float multiplier) {
    for (unsigned int i = 0; i < layer.biases.size(); ++i) {
        layer.biases[i] += bias[i] * multiplier;
    }

    for (unsigned int i = 0; i < layer.weights.size(); ++i) {
        layer.weights[i] += weight[i] * multiplier;
    }
}