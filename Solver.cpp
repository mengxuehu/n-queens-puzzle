
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
    positions = new int[N];
    num_conflict = new int[N]{};
    diag_positive = new int[N << 1]{};  // 1 to 2N-1
    diag_negative = new int[(N << 1)]{};  // 0 to 2N-2
}

Solver::~Solver() {
    delete[](positions);
    delete[](num_conflict);
    delete[](diag_positive);
    delete[](diag_negative);
}

void Solver::solve() {
    auto start = std::chrono::system_clock::now();
    init();

    bool flag = true;
    while (flag) {
        flag = false;
        for (int x1 = 0; x1 < N; ++x1) {
            if (num_conflict[x1] != 0) {
                int p11 = positions[x1] - x1 + N, n11 = positions[x1] + x1;
                for (int x2 = 0; x2 < N; ++x2) {
                    int p12 = positions[x1] - x2 + N, n12 = positions[x1] + x2;
                    int p21 = positions[x2] - x1 + N, n21 = positions[x2] + x1;

                    int diff = diag_positive[p21] + diag_negative[n21] + diag_positive[p12] + diag_negative[n12]
                               + (int(p21 == p12 || n21 == n12) << 1) - (num_conflict[x1] + num_conflict[x2]);

                    if (diff < 0) {
                        ++diag_positive[p21];
                        ++diag_negative[n21];
                        ++diag_positive[p12];
                        ++diag_negative[n12];

                        --diag_positive[p11];
                        --diag_negative[n11];
                        --diag_positive[positions[x2] - x2 + N];
                        --diag_negative[positions[x2] + x2];

                        num_conflict[x1] = diag_positive[p21] + diag_negative[n21] - 2;
                        num_conflict[x2] = diag_positive[p12] + diag_negative[n12] - 2;

                        int tmp = positions[x2];
                        positions[x2] = positions[x1];
                        positions[x1] = tmp;

                        if ((total_conflict -= diff) == 0) {
                            goto done;
                        }

                        flag = true;
                        break;
                    }
                }
                continue;
                // TODO: continue?
            }
        }
    }

    done:
    cout << "run time: " << (std::chrono::system_clock::now() - start).count() / 1e9 << endl;

    for (int i = 0; i < N; ++i) {
        if (num_conflict[i] != 0) {
            std::cout << "error" << std::endl;
            break;
        }
    }

//    for (int i = 0; i < N; ++i) {
//        for (int j = i + 1; j < N; ++j) {
//            if (i - j == positions[i] - positions[j] || i - j == positions[j] - positions[i]) {
//                std::cout << "error" << std::endl;
//                return;
//            }
//        }
//    }
}

void Solver::init() {
    std::iota(positions, positions + N, 0);
    std::shuffle(positions, positions + N, std::default_random_engine(4));
//            (unsigned long) std::chrono::system_clock::now().time_since_epoch().count()));

    std::list<int> rest(positions, positions + N);
    std::list<int> x, y;

    int remaining = 0;
    std::list<int>::iterator item;

    for (int i = N - 1; i >= remaining; --i) {
        item = rest.begin();

        while (diag_positive[*item - i + N] > 0 || diag_negative[*item + i] > 0) {
            ++item;
            if (item == rest.end()) {
                cout << rest.size() << endl;
                x.push_back(i);
                y.push_back(*rest.begin());
                rest.erase(rest.begin());
                goto tag;
            }
        }

        if (item != rest.end()) {
            positions[i] = *item;
            diag_positive[*item - i + N] = 1;
            diag_negative[*item + i] = 1;
            rest.erase(item);
        }
        tag:;
    }

    cout << y.size() << endl;

    auto it = y.begin();
    for (int j : x) {
        positions[j] = *(it++);
        diag_positive[positions[j] - j + N] += 1;
        diag_negative[positions[j] + j] += 1;
    }

    for (int i = 0; i < N; ++i) {
        num_conflict[i] = diag_positive[positions[i] - i + N] + diag_negative[positions[i] + i] - 2;
        total_conflict += num_conflict[i];
    }

}
