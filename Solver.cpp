
#include <iostream>
#include <chrono>
#include <algorithm>

using std::cout;
using std::endl;

#include "Solver.h"

Solver::Solver() {
    positions = new int[N];
    diag_positive = new int[N << 1];  // 1 to 2N-1
    diag_negative = new int[(N << 1)];  // 0 to 2N-2
}

Solver::~Solver() {
    delete[](positions);
    delete[](diag_positive);
    delete[](diag_negative);
}

void Solver::solve() {
    auto start = std::chrono::system_clock::now();
    std::fill(diag_positive, diag_positive + (N << 1), 0);
    std::fill(diag_negative, diag_negative + (N << 1), 0);
    init();

    bool flag = true;
    while (flag) {
        for (int x1 = 0; x1 < N; ++x1) {
            int p11 = positions[x1] - x1 + N, n11 = positions[x1] + x1;
            if (diag_positive[p11] != 1 || diag_negative[n11] != 1) {
                for (int x2 = 0; x2 < N; ++x2) {
                    int p22 = positions[x2] - x2 + N, n22 = positions[x2] + x2;
                    int p12 = positions[x1] - x2 + N, n12 = positions[x1] + x2;
                    int p21 = positions[x2] - x1 + N, n21 = positions[x2] + x1;

                    int dist = (diag_positive[p21] + diag_negative[n21] + diag_positive[p12] + diag_negative[n12]) -
                               (diag_positive[p11] + diag_negative[n11] + diag_positive[p22] + diag_negative[n22] - 4) +
                               (((p11 == p22) ^ (n11 == n22)) << 1);
                    if (dist < 0) {
                        ++diag_positive[p21];
                        ++diag_negative[n21];
                        ++diag_positive[p12];
                        ++diag_negative[n12];

                        --diag_positive[p11];
                        --diag_negative[n11];
                        --diag_positive[p22];
                        --diag_negative[n22];

                        int tmp = positions[x2];
                        positions[x2] = positions[x1];
                        positions[x1] = tmp;


                        if ((total_conflict += dist) == 0) {
                            goto done;
                        }

                        flag = true;
                        break;
                    }
                }
            }
        }
    }

    done:

    cout << "run time: " << (std::chrono::system_clock::now() - start).count() / 1e9 << endl;

    if (total_conflict != 0) {
        cout << "restart is required" << endl;
    }

//    std::fill(diag_positive, diag_positive + (N << 1), 0);
//    std::fill(diag_negative, diag_negative + (N << 1), 0);
//    for (int i = 0; i < N; ++i) {
//        if (diag_positive[positions[i] - i + N] != 0 || diag_negative[positions[i] + i] != 0) {
//            cout << "error" << endl;
//            break;
//        }
//        diag_positive[positions[i] - i + N] += 1;
//        diag_negative[positions[i] + i] += 1;
//    }
}

void Solver::init() {
    int *rest = new int[N + 1];
    int *end = rest + N;
    std::iota(rest, rest + N, 0);
    std::shuffle(rest, rest + N, std::default_random_engine(
            (unsigned long) std::chrono::system_clock::now().time_since_epoch().count()));

    int remaining = N / 10000;

    int *begin = rest;

    for (int i = N - 1; i >= remaining; --i) {
        int *item = begin;

        for (; item != end && (diag_positive[*item - i + N] > 0 || diag_negative[*item + i] > 0); ++item);

        if (item != end) {
            positions[i] = *item;
            diag_positive[*item - i + N] = 1;
            diag_negative[*item + i] = 1;
            *item = *(begin++);
        } else {
            break;
        }
    }

    int idx = 0;
    for (int *i = begin; i != end; ++i) {
        diag_positive[*i - idx + N] += 1;
        diag_negative[*i + idx] += 1;
        positions[idx++] = *i;
    }

    delete[](rest);

    for (int i = 0; i < N; ++i) {
        total_conflict += diag_positive[positions[i] - i + N] + diag_negative[positions[i] + i] - 2;//num_conflict[i];
    }
    total_conflict >>= 1;
}
