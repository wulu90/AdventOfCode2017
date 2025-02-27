#include <fstream>
#include <map>

using namespace std;

tuple<int, int, int> dir_string_to_adjacent(const tuple<int, int, int>& curr, const string& str) {
    static const map<string, tuple<int, int, int>> dir_delta{{"n", {-1, 0, 1}}, {"ne", {0, -1, 1}}, {"se", {1, -1, 0}},
                                                             {"s", {1, 0, -1}}, {"sw", {0, 1, -1}}, {"nw", {-1, 1, 0}}};

    auto [r, s, q]    = curr;
    auto [dr, ds, dq] = dir_delta.at(str);
    return {r + dr, s + ds, q + dq};
}

void part1() {
    ifstream input("input/input11");
    tuple<int, int, int> curr{0, 0, 0};    // r,s,q coordinate;
    for (string line; getline(input, line, ',');) {
        if (line.back() == '\n' || line.back() == '\r') {
            line.pop_back();
        }
        curr = dir_string_to_adjacent(curr, line);
    }
    println("{}", curr);    // r,s,q coordinate abs value max is the minmal steps from 0,0,0
}

int main() {
    part1();
    return 0;
}
