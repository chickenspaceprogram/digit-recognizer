#include <vector>
#include <iostream>
#include "libs/rand.hpp"
#include "train.hpp"
#include "libs/load-img.hpp"


#define NUM_HIDDEN 2
#define HIDDEN_SIZE 16
#define GRADIENT_MULT -0.2
#define BATCH_SIZE 100
#define NUM_ITERS 100

int main(void) {
    seed_rand();
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
    ReLU actfn;
    SquaredErr costfn;

    Network net(train_inputs[0].size(), HIDDEN_SIZE, train_outputs[0].size(), NUM_HIDDEN, GRADIENT_MULT);
    std::cout << "Network initialized!" << std::endl;
    Derivatives derivs;
    for (int i = 0; i < NUM_ITERS; ++i) {
        derivs = train_once(net, train_inputs, train_outputs, BATCH_SIZE, actfn, costfn);
        net.AddDerivatives(derivs, (float)GRADIENT_MULT / BATCH_SIZE);
        printf("%d\n", i);
    }
    train_once(net, train_inputs, train_outputs, BATCH_SIZE, actfn, costfn);
    std::cout << "One backtrack performed!" << std::endl;
}