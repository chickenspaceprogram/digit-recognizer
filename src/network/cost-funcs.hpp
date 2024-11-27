#ifndef COST_FUNCS_HPP
#define COST_FUNCS_HPP

#define NOT_SAME_LEN 1

#include <vector>

class CostFunction {
    public:
        virtual float Function(std::vector<float> &output, std::vector<float> &target);
        virtual std::vector<float> Derivative(std::vector<float> &output, std::vector<float> &target);
};

class SquaredErr : CostFunction {
    public:
        virtual float Function(std::vector<float> &output, std::vector<float> &target);
        virtual std::vector<float> Derivative(std::vector<float> &output, std::vector<float> &target);
};

#endif