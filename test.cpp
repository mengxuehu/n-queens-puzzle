
#include <iostream>

#include "Solver.h"

int main() {
    Solver solver;
    long sum = 0;
    for (int i = 0; i < 10; ++i) {
        sum += solver.solve();
    }
    sum /= 10;
    std::cout << sum / 1e9 << std::endl;
    return 0;
}