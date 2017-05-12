
//#include <set>
#include <iostream>

#include "Solver.h"

Solver::Solver() {
}

void Solver::solve() {
    init_position();
    init_conflict();
//    for (int x1 : conflict_pos) {
//        int old_num_conflict_x1 = num_conflict_at(x1, positions[x1]);
//        for (int x2 : conflict[x1]) {
//            int old_num_conflict_x2 = num_conflict_at(x2, positions[x2]);
//            int new_num_conflict_x1 = num_conflict_at(x1, positions[x2]);
//            int new_num_conflict_x2 = num_conflict_at(x2, positions[x1]);
//            if (new_num_conflict_x1 + new_num_conflict_x2 < old_num_conflict_x1 + old_num_conflict_x2) {
//
//            }
//        }
//    }
    bool flag = true;
    while (flag) {
        flag = false;
        for (int x1 = 0; x1 < N; ++x1) {
            if (num_conflict[x1] != 2) {
                int p11 = positions[x1] - x1 + N, n11 = positions[x1] + x1;
                for (int x2 = 0; x2 < N; ++x2) {
//                int p22 = positions[x2] - x2, n22 = positions[x2] + x2;
                    int p12 = positions[x1] - x2 + N, n12 = positions[x1] + x2;
                    int p21 = positions[x2] - x1 + N, n21 = positions[x2] + x1;

                    if (diag_positive[p21] + diag_negative[n21] + diag_positive[p12] + diag_negative[n12]
                        < num_conflict[x1] + num_conflict[x2]) {
                        ++diag_positive[p21];
                        ++diag_negative[n21];
                        ++diag_positive[p12];
                        ++diag_negative[n12];

                        --diag_positive[p11];
                        --diag_negative[n11];
                        --diag_positive[positions[x2] - x2 + N];
                        --diag_negative[positions[x2] + x2];

                        num_conflict[x1] = diag_positive[p21] + diag_negative[n21];
                        num_conflict[x2] = diag_positive[p12] + diag_negative[n12];

                        int tmp = positions[x2];
                        positions[x2] = positions[x1];
                        positions[x1]= tmp;

                        flag = true;
                        break;
                    }

//                int old_x1 = num_conflict[x1];
//                int old_x2 = num_conflict[x2];
//
//                int new_x1 = diag_positive[p21] + diag_negative[n21];
////                        num_conflict_at(x1, positions[x2]);
//                int new_x2 = diag_positive[p12] + diag_negative[n12];
//                        num_conflict_at(x2, positions[x1]);
//                if (new_x1 + new_x2 < old_x1 + old_x2) {
//                    --diag_positive[positions[x1] - x1];
//                    --diag_positive[positions[x2] - x2];
//                    --diag_negative[positions[x1] + x1];
//                    --diag_negative[positions[x2] + x2];
//
//                    int tmp = positions[x2];
//                    positions[x2] = positions[x1];
//                    positions[x1] = tmp;
//                    num_conflict[x1] = new_x1;
//                    num_conflict[x2] = new_x2;
//
//                    diag_positive[p21] = diag_positive[p21] - old_x1 + new_x1;
//
//                    break;
//                }

                }
                // TODO: continue?
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j == positions[i]) {
                std::cout << positions[i];
            } else {
                std::cout << "_";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Solver::init_position() {
    for (int i = 0; i < N; ++i) {
        positions[i] = i;
    }
}

void Solver::init_conflict() {
    for (int i = 0; i < N; ++i) {
        diag_positive[positions[i] - i + N] += 1;
        diag_negative[positions[i] + i] += 1;
    }

    for (int i = 0; i < N; ++i) {
        ++num_conflict[i];
        for (int j = i + 1; j < N; ++j) {
            if (i - j == positions[i] - positions[j]) {
                conflict_pos.push_back(i);
                conflict[i].insert(j);
//                diag_positive[positions[i] - i + N] += 1;

                ++num_conflict[i];
                ++num_conflict[j];
//                conflict[i].insert(j);
//                conflict.push_back(std::make_pair(i, j));
            } else if (i - j == positions[j] - positions[i]) {
                conflict_pos.push_back(i);
                conflict[i].insert(j);
//                diag_negative[positions[i] + i] += 1;
                ++num_conflict[i];
                ++num_conflict[j];
//                diag_negative[i + j] += 1;
            }
//            if (i - j == positions[i] - positions[j]
//                    || i - j == positions[j] - positions[i]) {
//                conflict_pos.push_back(i);
//                conflict[i].insert(j);
//                diag[positions[i] - positions[j]] += 1;
////                conflict[i].insert(j);
////                conflict.push_back(std::make_pair(i, j));
//            }
        }
    }
}

bool Solver::is_conflict(int x1, int x2, int y1, int y2) {

}

inline int Solver::num_conflict_at(int x, int y) {
    return diag_positive[y - x] + diag_negative[y + x];
}
