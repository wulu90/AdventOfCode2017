#include <charconv>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<pair<int, int>> find_next(const vector<pair<int, int>>& component_vec, int curr_port, const vector<pair<int, int>>& bridge) {
    set<pair<int, int>> opts;

    for (auto& comp : component_vec) {
        if (comp.first == curr_port || comp.second == curr_port) {
            opts.insert(comp);
        }
    }
    for (auto& o : bridge) {
        if (opts.contains(o)) {
            opts.erase(o);
        }
    }
    return opts;
}

void backtrace(const vector<pair<int, int>> component_vec, int& strongest, pair<int, int>& len_strength, int curr_port,
               vector<pair<int, int>> bridge) {
    auto opts = find_next(component_vec, curr_port, bridge);
    for (auto& op : opts) {
        bridge.push_back(op);
        backtrace(component_vec, strongest, len_strength, op.first == curr_port ? op.second : op.first, bridge);
        bridge.pop_back();
    }
    int strength = 0;
    for (auto& b : bridge) {
        strength += b.first + b.second;
    }
    // println("{},{}", strength, bridge);

    strongest = max(strongest, strength);

    if (bridge.size() >= len_strength.first) {
        len_strength.first  = bridge.size();
        len_strength.second = max(len_strength.second, strength);
    }
}

void part1_2() {
    ifstream input("input/input24");
    multimap<int, int> conn_map;
    vector<pair<int, int>> component_vec;
    for (string line; getline(input, line);) {
        auto p = line.find('/');
        int i  = 0;
        int j  = 0;
        from_chars(line.data(), line.data() + p, i);
        from_chars(line.data() + p + 1, line.data() + line.size(), j);
        component_vec.push_back({i, j});
        conn_map.insert({i, j});
        if (i != 0 && i != j) {
            conn_map.insert({j, i});
        }
    }
    int strongest = 0;
    pair<int, int> len_strength;
    backtrace(component_vec, strongest, len_strength, 0, {});
    println("{}", strongest);
    println("{}", len_strength.second);
}

int main() {
    part1_2();
    return 0;
}
