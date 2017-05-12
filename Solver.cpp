
//#include <set>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include <list>

using std::cout;
using std::endl;

#include "Solver.h"

Solver::Solver() {
//    positions = new int[N];
//    num_conflict = new int[N]{};
//    diag_positive = new int[N << 1]{};  // 1 to 2N-1
//    diag_negative = new int[(N << 1)]{};  // 0 to 2N-2
}

Solver::~Solver() {
//    delete[](positions);
//    delete[](num_conflict);
//    delete[](diag_positive);
//    delete[](diag_negative);
}

void Solver::solve() {
    auto start = std::chrono::system_clock::now();
    init_position();
//    init_conflict();

    bool flag = true;
    while (flag) {
        flag = false;
        for (int x1 = 0; x1 < N; ++x1) {
            if (num_conflict[x1] != 2) {
                int p11 = positions[x1] - x1 + N, n11 = positions[x1] + x1;
                for (int x2 = 0; x2 < N; ++x2) {
                    int p12 = positions[x1] - x2 + N, n12 = positions[x1] + x2;
                    int p21 = positions[x2] - x1 + N, n21 = positions[x2] + x1;

                    if (diag_positive[p21] + diag_negative[n21] + diag_positive[p12] + diag_negative[n12] + 4
                        + (int(p21 == p12 || n21 == n12) << 1) < num_conflict[x1] + num_conflict[x2]) {
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
                        positions[x1] = tmp;

                        flag = true;
                        break;
                    }
                }
                continue;
                // TODO: continue?
            }
        }
    }


    cout << "run time: " << (std::chrono::system_clock::now() - start).count() / 1e9 << endl;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (i - j == positions[i] - positions[j] || i - j == positions[j] - positions[i]) {
                std::cout << "error" << std::endl;
                return;
            }
        }
    }
}

void Solver::init_position() {
    std::iota(positions, positions + N, 0);
    std::shuffle(positions, positions + N, std::default_random_engine(
            (unsigned long) std::chrono::system_clock::now().time_since_epoch().count()));

    std::list<int> rest(positions, positions + N);
    int remaining = 200;
    std::list<int>::iterator item;
    int i = N - 1;
    for (; i >= remaining; --i) {
        item = rest.begin();

        while (diag_positive[*item - i + N] > 0 || diag_negative[*item + i] > 0) {
            ++item;
            if (item == rest.end()) {
                cout << "momo" << endl;
            }
        }

        if (item != rest.end()) {
            positions[i] = *item;
            diag_positive[*item - i + N] = 1;
            diag_negative[*item + i] = 1;
            num_conflict[i] = 2;
            rest.erase(item);
        } else {
            cout << "haha" << endl;
        }
    }

    item = rest.begin();
    for (; i > -1; ++item, --i) {
        positions[i] = *item;
        diag_positive[*item - i + N] += 1;
        diag_negative[*item + i] += 1;
//        num_conflict[i] = diag_positive[*item - i + N] + diag_negative[*item + i];
    }

    for (int k = 0; k < remaining; ++k) {
        num_conflict[k] += 2;
        for (int j = k + 1; j < remaining; ++j) {
            if (k - j == positions[k] - positions[j] || k - j == positions[j] - positions[k]) {
                ++num_conflict[k];
                ++num_conflict[j];
            }
        }
    }
}

void Solver::init_conflict() {
//    for (int i = 0; i < N; ++i) {
//        diag_positive[positions[i] - i + N] += 1;
//        diag_negative[positions[i] + i] += 1;
//    }

    for (int i = 0; i < N; ++i) {
        num_conflict[i] += 2;
        for (int j = i + 1; j < N; ++j) {
            if (i - j == positions[i] - positions[j] || i - j == positions[j] - positions[i]) {
                ++num_conflict[i];
                ++num_conflict[j];
            }
        }
    }
}
