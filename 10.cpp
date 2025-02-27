#include <fstream>
#include <numeric>
#include <vector>

using namespace std;

void hash_step(array<int, 256>& numlist, int& position, int& skip, int len) {
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

void part1() {
    ifstream input("input/input10");
    vector<int> len_vec;
    for (int n; input >> n;) {
        len_vec.push_back(n);
        input.get();
    }

    array<int, 256> numlist;
    iota(numlist.begin(), numlist.end(), 0);

    int position = 0;
    int skip     = 0;

    for (auto len : len_vec) {
        hash_step(numlist, position, skip, len);
    }

    println("{}", numlist[0] * numlist[1]);
}

void part2() {
    ifstream input("input/input10");
    vector<int> len_vec;

    for (char c = input.get(); c != '\r' && c != '\n'; c = input.get()) {
        len_vec.push_back(c);
    }

    len_vec.push_back(17);
    len_vec.push_back(31);
    len_vec.push_back(73);
    len_vec.push_back(47);
    len_vec.push_back(23);

    array<int, 256> numlist;
    iota(numlist.begin(), numlist.end(), 0);

    int position = 0;
    int skip     = 0;

    for (int i = 0; i < 64; ++i) {
        for (auto len : len_vec) {
            hash_step(numlist, position, skip, len);
        }
    }

    vector<int> dence_hash;
    for (int i = 0; i < 16; ++i) {
        int dence = numlist[i * 16];
        for (int j = 1; j < 16; ++j) {
            dence ^= numlist[i * 16 + j];
        }
        dence_hash.push_back(dence);
    }

    string knot_hash;
    string hexchars = "0123456789abcdef";
    for (auto dence : dence_hash) {
        knot_hash.push_back(hexchars[(dence & 0xf0) >> 4]);
        knot_hash.push_back(hexchars[dence & 0x0f]);
    }

    println("{}", knot_hash);
}

int main() {
    part1();
    part2();
    return 0;
}
