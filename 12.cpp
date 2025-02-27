#include <charconv>
#include <fstream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

pair<int, vector<int>> parse(const string& str) {
    auto sp_v = str | views::split(" <-> "sv);
    auto it   = sp_v.begin();
    string_view lhs_sv{*it};
    int lhs = 0;
    from_chars(lhs_sv.begin(), lhs_sv.end(), lhs);
    ++it;
    auto rhs_v = string_view{*it} | views::split(", "sv) | views::transform([](auto&& subv) -> int {
                     int num = 0;
                     from_chars(subv.begin(), subv.end(), num);
                     return num;
                 }) |
                 ranges::to<vector>();
    return {lhs, rhs_v};
}

void part1() {
    ifstream input("input/input12");
    map<int, vector<int>> comm_mat;
    for (string line; getline(input, line);) {
        auto [lhs, rhs_v] = parse(line);
        for (auto rhs : rhs_v) {
            comm_mat[lhs].push_back(rhs);
            comm_mat[rhs].push_back(lhs);
        }
    }

    queue<int> q;
    q.push(0);

    set<int> group_zero;
    group_zero.insert(0);

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        for (auto adj : comm_mat[curr]) {
            if (!group_zero.contains(adj)) {
                q.push(adj);
                group_zero.insert(adj);
            }
        }
    }

    println("{}", group_zero.size());
}

int main() {
    part1();
    return 0;
}
