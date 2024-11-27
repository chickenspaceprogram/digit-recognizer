#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "network/network.hpp"
#include "network/cost-funcs.hpp"
#include <stdio.h>

// this is a bad way to do this but i'm not fixing it
#define INPUT_ERROR 100
#define TARGET_ERROR 101
#define INPUT_TARGET_INVALID_LEN 102


// num_inputs : the number of inputs to use in the training
// learning_multiplier > 0 for training to happen
Derivatives train_once(Network &network, std::vector<std::vector<float>> &input, std::vector<std::vector<float>> &target, int num_inputs, ActivationFunction &act_fn, CostFunction &cost_fn, ActivationFunction &end_activation_fn);

#endif