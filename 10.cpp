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

int main() {
    part1();
    return 0;
}
