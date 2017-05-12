
#ifndef N_QUEENS_PUZZLE_SOLVER_H
#define N_QUEENS_PUZZLE_SOLVER_H

#define N 3

#include <list>
#include <map>
#include <set>
#include <vector>
#include <utility>
//#include <bits/unordered_set.h>

class Solver {
public:
    Solver();

    void solve();

private:
    void init_position();

    void init_conflict();

    bool is_conflict(int x1, int x2, int y1, int y2);

//    bool test_swap(int x, int y);

    inline int num_conflict_at(int x, int y);

private:
    int positions[N];

    // TODO order or unorder
    std::list<int> conflict_pos;
    std::set<int> conflict[N];

    int num_conflict[N] = {};
//    int diag[(N << 1) -1] = {};
    int diag_positive[(N << 1) - 1] = {};
    int diag_negative[(N << 1) - 1] = {};
//    int diag[(N << 1) - 1][2] = {};

//    std::list<std::pair<int, int>> conflict;
};


#endif //N_QUEENS_PUZZLE_SOLVER_H
