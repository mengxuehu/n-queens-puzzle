
#ifndef N_QUEENS_PUZZLE_SOLVER_H
#define N_QUEENS_PUZZLE_SOLVER_H

#define N 1000000

class Solver {
public:
    Solver();

    ~Solver();

    void solve();

private:
    void init();

private:
    int *positions;
    int *diag_positive;  // 1 to 2N-1
    int *diag_negative;  // 0 to 2N-2

    int total_conflict = 0;
};


#endif //N_QUEENS_PUZZLE_SOLVER_H
