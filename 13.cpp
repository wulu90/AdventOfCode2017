#include <charconv>
#include <fstream>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

pair<int, int> parse(const string& str) {
    auto a = string_view{str} | views::split(": "sv) | views::transform([](auto&& subv) {
                 int num = 0;
                 from_chars(subv.begin(), subv.end(), num);
                 return num;
             }) |
             ranges::to<vector>();
    return {a[0], a[1]};    // 🙃
}

void part1() {
    ifstream input("input/input13");
    map<int, int> depth_range;
    for (string line; getline(input, line);) {
        depth_range.insert(parse(line));
    }
    depth_range.erase(0);

    int severity = 0;
    for (auto [d, r] : depth_range) {
        // every -1+(r-1)*2n picosecond, scaner is in range0
        // "d" picosecond you enter
        // so just check last picosecond (d-1), wheather scanner is in range 0
        // -1+(r-1)*2n=d-1;
        if (d % (2 * (r - 1)) == 0) {
            severity += d * r;
        }
    }
    println("{}", severity);
}

int main() {
    part1();
    return 0;
}
