#include <array>
#include <fstream>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

using namespace std;

void hash_step(array<uint8_t, 256>& numlist, uint8_t& position, uint8_t& skip, uint8_t len) {
    vector<int> vec;
    vec.resize(len);    // !!!
    auto forward  = len > 256 - position ? 256 - position : len;
    auto backward = len > 256 - position ? len - (256 - position) : 0;

    copy_n(numlist.begin() + position, forward, vec.begin());
    copy_n(numlist.begin(), backward, vec.begin() + forward);

    copy_n(vec.rbegin(), forward, numlist.begin() + position);
    copy_n(vec.rbegin() + forward, backward, numlist.begin());

    position = (position + len + skip) % 256;
    ++skip;
}

array<uint8_t, 16> knot_hash(const string& str) {
    vector<uint8_t> len_vec;

    for (char c : str) {
        len_vec.push_back(c);
    }

    len_vec.push_back(17);
    len_vec.push_back(31);
    len_vec.push_back(73);
    len_vec.push_back(47);
    len_vec.push_back(23);

    array<uint8_t, 256> numlist;
    iota(numlist.begin(), numlist.end(), 0);

    uint8_t position = 0;
    uint8_t skip     = 0;

    for (int i = 0; i < 64; ++i) {
        for (auto len : len_vec) {
            hash_step(numlist, position, skip, len);
        }
    }

    array<uint8_t, 16> dence_hash;
    for (size_t i = 0; i < 16; ++i) {
        uint8_t dence = numlist[i * 16];
        for (size_t j = 1; j < 16; ++j) {
            dence ^= numlist[i * 16 + j];
        }
        dence_hash[i] = dence;
    }

    return dence_hash;
}

void part1() {
    ifstream input("input/input14");
    string line;
    getline(input, line);

    uint32_t used = 0;
    for (size_t i = 0; i < 128; ++i) {
        auto hash_uint_array = knot_hash(line + format("-{}", i));
        for (auto v : hash_uint_array) {
            used += popcount(v);
        }
    }

    println("{}", used);
}

void part2() {
    ifstream input("input/input14");
    string line;
    getline(input, line);

    array<array<uint8_t, 16>, 128> diskuesd;
    for (size_t i = 0; i < 128; ++i) {
        diskuesd[i] = knot_hash(line + format("-{}", i));
    }

    auto isused = [&diskuesd](size_t i, size_t j) {
        uint8_t flag = 1 << (7 - j % 8);
        return (diskuesd[i][j / 8] & flag) == flag;
    };

    set<pair<size_t, size_t>> grouped;
    uint32_t group_count = 0;
    for (size_t i = 0; i < 128; ++i) {
        for (size_t j = 0; j < 128; ++j) {
            if (isused(i, j) && !grouped.contains({i, j})) {
                ++group_count;
                queue<pair<size_t, size_t>> q;
                q.push({i, j});

                while (!q.empty()) {
                    auto curr = q.front();
                    q.pop();

                    static const array<array<int, 2>, 4> deltas{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

                    for (auto [dr, dc] : deltas) {
                        auto r = curr.first + dr;
                        auto c = curr.second + dc;
                        if (r < 128 && c < 128 && isused(r, c) && !grouped.contains({r, c})) {
                            q.push({r, c});
                            grouped.insert({r, c});
                        }
                    }
                }
            }
        }
    }

    println("{}", group_count);
}

int main() {
    part1();
    part2();
    return 0;
}
