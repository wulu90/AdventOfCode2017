#include <fstream>
#include <numeric>
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

int main() {
    part1();
    return 0;
}
