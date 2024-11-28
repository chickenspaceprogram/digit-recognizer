#include <vector>
#include <iostream>
#include <fenv.h>
#pragma STDC FENV_ACCESS ON
#include "libs/rand.hpp"
#include "train.hpp"
#include "libs/load-img.hpp"


#define NUM_HIDDEN 10
#define HIDDEN_SIZE 16
#define GRADIENT_MULT 0.01
#define BATCH_SIZE 100
#define NUM_ITERS 1000

int main(void) {
    seed_rand();
    fexcept_t flags;
    fegetexceptflag(&flags, FE_ALL_EXCEPT);
    fesetexceptflag(&flags, FE_ALL_EXCEPT);
    std::cout << "Starting..." << std::endl;
    std::vector<std::vector<float>> train_inputs;
    std::vector<std::vector<float>> train_outputs;
    std::vector<std::vector<float>> test_inputs;
    std::vector<std::vector<float>> test_outputs;
    try {
        train_inputs = GetImages((char *)"mnist-dataset/train-images-idx3-ubyte");
        train_outputs = GetLabels((char *)"mnist-dataset/train-labels-idx1-ubyte");
        test_inputs = GetImages((char *)"mnist-dataset/t10k-images-idx3-ubyte");
        test_outputs = GetLabels((char *)"mnist-dataset/t10k-labels-idx1-ubyte");
    }
    catch (char const *exception) {
        std::cout << exception << std::endl;
    }
    std::cout << "Loaded images!" << std::endl;
    ReLU6 actfn;
    ReLU6 endactfn;
    SquaredErr costfn;

    Network net(train_inputs[0].size(), HIDDEN_SIZE, train_outputs[0].size(), NUM_HIDDEN, GRADIENT_MULT / BATCH_SIZE);
    std::cout << "Network initialized!" << std::endl;
    Derivatives derivs;
    for (int i = 0; i < NUM_ITERS; ++i) {
        derivs = train_once(net, train_inputs, train_outputs, BATCH_SIZE, actfn, costfn, endactfn);
        net.AddDerivatives(derivs);
        printf("%d\n", i);
    }
    

}