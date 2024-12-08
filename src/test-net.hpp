#ifndef TEST_NET_HPP
#define TEST_NET_HPP

#include <vector>
#include "network/network.hpp"
#include "network/activation-funcs.hpp"

int get_successes(
    Network &net, 
    std::vector<std::vector<float>> &inputs,
    std::vector<std::vector<float>> &outputs,
    ActivationFunction &act_fn,
    ActivationFunction &end_act_fn
);

int get_max(std::vector<float> &outputs);

#endif