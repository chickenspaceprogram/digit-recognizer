#include "cost-funcs.hpp"

float SquaredErr::Function(std::vector<float> &output, std::vector<float> &target) {
    float err = 0;
    if (output.size() != target.size()) {
        throw NOT_SAME_LEN;
    }
    for (unsigned int i = 0; i < output.size(); ++i) {
        err += 0.5 * (target[i] - output[i]) * (target[i] - output[i]);
    }
    return err;
}

std::vector<float> SquaredErr::Derivative(std::vector<float> &output, std::vector<float> &target) {
    std::vector<float> out;
    if (output.size() != target.size()) {
        throw NOT_SAME_LEN;
    }
    for (unsigned int i = 0; i < output.size(); ++i) {
        out.push_back(target[i] - output[i]);
    }
    return out;
}