#include "network.hpp"

Network::Network(int input_len, int hidden_len, int output_len, int num_hidden_layers, float gradient_mult) : 
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
    for (unsigned int i = 0; i < hidden.size(); ++i) {
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

void Network::RunNetwork(ActivationFunction &fn, ActivationFunction &end_actfn) {
    hidden[0].SetActivations(start, fn);
    for (unsigned int i = 1; i < hidden.size(); ++i) {
        hidden[i].SetActivations(hidden[i - 1], fn);
    }
    end.SetActivations(hidden[hidden.size() - 1], end_actfn);
}

void Network::BackProp(ActivationFunction &fn, ActivationFunction &end_actfn) {
    end.CalcGradients(hidden[hidden.size() - 1], end_actfn);
    for (int i = hidden.size() - 1; i > 0; --i) {
        hidden[i].CalcGradients(hidden[i - 1], fn);
    }
    hidden[0].CalcGradients(start, fn);
}

Derivatives Network::GetCurrentDerivatives() {
    Derivatives derivs;
    derivs.input = LayerDerivatives::GetLayerDerivatives(start);
    derivs.output = LayerDerivatives::GetLayerDerivatives(end);
    for (int i = 0; i < num_hidden_layers; ++i) {
        derivs.hidden.push_back(LayerDerivatives::GetLayerDerivatives(hidden[i]));
    }
    return derivs;
}

void Network::AddDerivatives(Derivatives &derivs) {
    derivs.input.SetLayerDerivatives(start, gradient_mult);
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
    input += derivs.input;
    output += derivs.output;
    for (unsigned int i = 0; i < hidden.size(); ++i) {
        hidden[i] += derivs.hidden[i];
    }
}

LayerDerivatives LayerDerivatives::GetLayerDerivatives(Layer &layer) {
    LayerDerivatives lderivs;
    lderivs.bias = layer.activations_deriv;
    lderivs.weight = layer.weights_deriv;
    return lderivs;
}

void LayerDerivatives::SetLayerDerivatives(Layer &layer, float multiplier) {
    for (unsigned int i = 0; i < layer.activations_deriv.size(); ++i) {
        //printf("%f", layer.biases[i]);
        layer.biases[i] += bias[i] * multiplier;
    }

    for (unsigned int i = 0; i < layer.weights_deriv.size(); ++i) {
        layer.weights[i] += weight[i] * multiplier;
    }
}