#include <vector>
#include <iostream>
#include <fenv.h>
#include <assert.h>
#include "libs/rand.hpp"
#include "train.hpp"
#include "libs/load-img.hpp"
#include "test-net.hpp"


#define NUM_HIDDEN 2
#define HIDDEN_SIZE 16
#define GRADIENT_MULT 0.1
#define BATCH_SIZE 500
#define NUM_ITERS 20000
#define IMG_VARIANCE 1
#define ACTIVATION_MULTIPLIER 0.3

int main(void) {
    seed_rand();
    std::cout << "Starting..." << std::endl;
    std::vector<std::vector<float>> train_inputs;
    std::vector<std::vector<float>> train_outputs;
    std::vector<std::vector<float>> test_inputs;
    std::vector<std::vector<float>> test_outputs;
    try {
        train_inputs = GetImages((char *)"mnist-dataset/train-images-idx3-ubyte", IMG_VARIANCE);
        train_outputs = GetLabels((char *)"mnist-dataset/train-labels-idx1-ubyte");
        test_inputs = GetImages((char *)"mnist-dataset/t10k-images-idx3-ubyte", IMG_VARIANCE);
        test_outputs = GetLabels((char *)"mnist-dataset/t10k-labels-idx1-ubyte");
    }
    catch (char const *exception) {
        std::cout << exception << std::endl;
    }
    std::cout << "Loaded images!" << std::endl;
    Sigmoid actfn;
    Sigmoid endactfn;
    SquaredErr costfn;

    Network net(train_inputs[0].size(), HIDDEN_SIZE, train_outputs[0].size(), NUM_HIDDEN, GRADIENT_MULT / BATCH_SIZE, ACTIVATION_MULTIPLIER);
    std::cout << "Network initialized!\n\nRunning Network..." << std::endl;
    Derivatives derivs;
    FILE *fp = fopen("out.txt", "w");
    assert(fp != NULL);

    for (int i = 0; i < NUM_ITERS; ++i) {
        derivs = train_once(net, train_inputs, train_outputs, BATCH_SIZE, actfn, costfn, endactfn);
        net.AddDerivatives(derivs);
        fprintf(fp,"%d,", get_successes(net, test_inputs, test_outputs, actfn, endactfn));
    }
    

}