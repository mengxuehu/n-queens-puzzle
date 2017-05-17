
#include "Solver.h"

#include <iostream>

int main() {
    const int num = 10;
    Solver solver;
    long time = 0;
    for (int i = 0; i < num; ++i) {
        time += solver.solve();
    }

    std::cout << time / 1e9 << std::endl;
    return 0;
}
