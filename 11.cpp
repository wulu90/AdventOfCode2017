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

int abs_max(const tuple<int, int, int>& coord) {
    return max({abs(get<0>(coord)), abs(get<1>(coord)), abs(get<2>(coord))});
}

void part1_2() {
    ifstream input("input/input11");
    tuple<int, int, int> curr{0, 0, 0};    // r,s,q coordinate;
    int furthest_away = 0;
    for (string line; getline(input, line, ',');) {
        if (line.back() == '\n' || line.back() == '\r') {
            line.pop_back();
        }
        curr          = dir_string_to_adjacent(curr, line);
        furthest_away = max(furthest_away, abs_max(curr));
    }
    println("{}", curr);    // r,s,q coordinate abs value max is the minmal steps from 0,0,0
    println("{}", furthest_away);
}

int main() {
    part1_2();
    return 0;
}
