#ifndef COST_FUNCS_HPP
#define COST_FUNCS_HPP

#define NOT_SAME_LEN 1

#include <vector>

struct CostFunction {
        virtual float Function(std::vector<float> &output, std::vector<float> &target) = 0;
        virtual std::vector<float> Derivative(std::vector<float> &output, std::vector<float> &target) = 0;
};

struct SquaredErr : public CostFunction {
    virtual float Function(std::vector<float> &output, std::vector<float> &target);
    virtual std::vector<float> Derivative(std::vector<float> &output, std::vector<float> &target);
};

#endif