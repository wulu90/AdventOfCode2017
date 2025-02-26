#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

bool valid(const string& str) {
    set<string_view> svs;
    bool valid = true;
    for (auto sv : str | views::split(' ')) {
        if (svs.contains(string_view(sv))) {
            valid = false;
        } else {
            svs.insert(string_view(sv));
        }
    }
    return valid;
}

bool valid2(const string& str) {
    vector<string_view> svs;
    bool valid = true;
    for (auto sv : str | views::split(' ')) {
        for (auto sv_prev : svs) {
            if (is_permutation(sv.begin(), sv.end(), sv_prev.begin(), sv_prev.end())) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            break;
        }
        svs.push_back(string_view(sv));
    }
    return valid;
}

void part1_2() {
    ifstream input("input/input04");
    uint32_t valid_count  = 0;
    uint32_t valid2_count = 0;
    for (string line; getline(input, line);) {
        if (valid(line)) {
            ++valid_count;
        }
        if (valid2(line)) {
            ++valid2_count;
        }
    }

    println("{}", valid_count);
    println("{}", valid2_count);
}

int main() {
    part1_2();
    return 0;
}
