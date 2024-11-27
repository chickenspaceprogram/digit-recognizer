#include "train.hpp"

Derivatives train_once(Network &network, std::vector<std::vector<float>> &input, std::vector<std::vector<float>> &target, int num_inputs, ActivationFunction &act_fn, CostFunction &cost_fn) {
    if (input.size() == 0) {
        throw INPUT_ERROR;
    }
    if (target.size() == 0) {
        throw TARGET_ERROR;
    }
    if (input.size() != target.size()) {
        throw INPUT_TARGET_INVALID_LEN;
    }

    int input_len = input[0].size();
    int target_len = target[0].size();
    int rand_selection;

    Derivatives derivatives;

    for (int i = 0; i < num_inputs; ++i) {
        rand_selection = randint(0, input_len);
        network.SetInput(input[rand_selection]);
        network.RunNetwork(act_fn);
        printf("%f", cost_fn.Function(network.GetOutput(), target[i]));
        network.SetOutputDeriv(cost_fn.Derivative(network.GetOutput(), target[i]));
        network.BackProp(act_fn);
        if (i == 0) {
            derivatives = network.GetCurrentDerivatives();
            continue;
        }
        derivatives += network.GetCurrentDerivatives();
    }
    return derivatives; // gotta divide, yo
}