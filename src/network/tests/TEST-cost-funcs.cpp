#include "../cost-funcs.hpp"
#include <vector>

int main(void) {
    std::vector<float> out;
    out.push_back(0.1);
    out.push_back(0.3);
    out.push_back(0.5);
    out.push_back(0.7);
    out.push_back(0.9);

    std::vector<float> trg;
    trg.push_back(0);
    trg.push_back(1);
    trg.push_back(0);
    trg.push_back(0);
    trg.push_back(0);

    assert(SquaredErr::Function(out, trg) == 0.5 * (0.1 * 0.1 + (0.3 - 1) * (0.3 - 1) + 0.5 * 0.5 + 0.7 * 0.7 + 0.9 * 0.9));
    std::vector<float> deriv = SquaredErr::Derivative(out, trg)
}