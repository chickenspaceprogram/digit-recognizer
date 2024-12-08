#include "test-net.hpp"
#include <assert.h>

int get_successes(
    Network &net, 
    std::vector<std::vector<float>> &inputs,
    std::vector<std::vector<float>> &outputs,
    ActivationFunction &act_fn,
    ActivationFunction &end_act_fn
) {
    assert(inputs.size() == outputs.size());

    int correct_guesses = 0;
    for (int i = 0; i < inputs.size(); ++i) {
        net.SetInput(inputs[i]);
        net.RunNetwork(act_fn, end_act_fn);
        if (outputs[i][get_max(net.GetOutput())] > 0.9) { // using > 0.9 as a proxy for == 1 since float comparison could potentially cause issues
            ++correct_guesses;
        }
    }
    return correct_guesses;
}

int get_max(std::vector<float> &outputs) {
    assert(outputs.size() > 0);
    float max = outputs[0];
    int max_index = 0;
    for (int i = 1; i < outputs.size(); ++i) {
        if (outputs[i] > max) {
            max = outputs[i];
            max_index = i;
        }
    }
    return max_index;
}