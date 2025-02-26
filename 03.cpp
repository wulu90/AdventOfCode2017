#include <print>
#include <vector>

using namespace std;

void part1() {
    static const int input = 277678;
    int i                  = 0;
    while (4 * i * i + 4 * i + 1 <= input) {
        ++i;
    }
    i -= 1;
    int side      = 2 * i + 3;
    int left_mid  = 4 * i * i + 4 * i + 1 + 1 + i;
    int down_mid  = 4 * i * i + 4 * i + 1 + 1 + i + 2 * i + 2;
    int right_mid = 4 * i * i + 4 * i + 1 + 1 + i + 2 * i + 2 + 2 * i + 2;
    int up_mid    = 4 * i * i + 4 * i + 1 + 1 + i + 2 * i + 2 + 2 * i + 2 + 2 * i + 2;

    if (input < left_mid) {
        println("{}", left_mid - input + i + 1);
    }

    vector<int> midvec{up_mid, right_mid, down_mid, left_mid};

    for (size_t j = 0; j < 4; ++j) {
        if (input >= midvec[j]) {
            println("{}", input - midvec[j] + i + 1);
            break;
        }
    }
}

void part2() {
    static const int input = 277678;
    array<array<int, 101>, 101> mat;
    mat.fill({0});

    mat[50][50] = 1;
    array<array<int, 2>, 4> deltas{{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}};
    size_t rs = 50;
    size_t cs = 50;
    size_t r, c;
    for (size_t i = 1; i < 5; ++i) {
        auto len = 2 * i + 1;
        cs       = cs + 1;
        for (size_t j = 0; j < 4; ++j) {
            for (size_t k = 0; k < len - 1; ++k) {
                r         = rs + deltas[j][0] * k;
                c         = cs + deltas[j][1] * k;
                mat[r][c] = mat[r - 1][c] + mat[r - 1][c + 1] + mat[r][c + 1] + mat[r + 1][c + 1] + mat[r + 1][c] + mat[r + 1][c - 1] +
                            mat[r][c - 1] + mat[r - 1][c - 1];
                if (mat[r][c] > input) {
                    println("{}", mat[r][c]);
                    break;
                }
            }
            if (j < 3) {
                rs = r + deltas[j + 1][0];
                cs = c + deltas[j + 1][1];
            } else {
                rs = r;
                cs = c;
            }
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
