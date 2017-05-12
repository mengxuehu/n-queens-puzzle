
#ifndef N_QUEENS_PUZZLE_SOLVER_H
#define N_QUEENS_PUZZLE_SOLVER_H

#define N 10000000

#include <list>

class Solver {
public:
    Solver();

    ~Solver();

    void solve();

private:
    void init();

private:
//    int positions[N];
//    int num_conflict[N] = {};
//    int diag_positive[N << 1] = {};  // 1 to 2N-1
//    int diag_negative[(N << 1) - 1] = {};  // 0 to 2N-2
    int *positions;
    int *num_conflict;
    int *diag_positive;  // 1 to 2N-1
    int *diag_negative;  // 0 to 2N-2

    int total_conflict = 0;
};


#endif //N_QUEENS_PUZZLE_SOLVER_H
