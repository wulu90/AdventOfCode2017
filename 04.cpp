#include <fstream>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <string_view>

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

void part1() {
    ifstream input("input/input04");
    uint32_t valid_count = 0;
    for (string line; getline(input, line);) {
        if (valid(line)) {
            ++valid_count;
        }
    }

    println("{}", valid_count);
}

int main() {
    part1();
    return 0;
}
