
#ifndef N_QUEENS_PUZZLE_SOLVER_H
#define N_QUEENS_PUZZLE_SOLVER_H

#define N 10000

class Solver {
public:
    Solver();

    ~Solver();

    void solve();

private:
    void init_position();

    void init_conflict();

private:
    int positions[N];
    int num_conflict[N] = {};
    int diag_positive[N << 1] = {};  // 1 to 2N-1
    int diag_negative[(N << 1) - 1] = {};  // 0 to 2N-2
//    int *positions;
//    int *num_conflict;
//    int *diag_positive;  // 1 to 2N-1
//    int *diag_negative;  // 0 to 2N-2
};


#endif //N_QUEENS_PUZZLE_SOLVER_H
