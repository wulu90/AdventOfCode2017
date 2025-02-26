#include <fstream>
#include <print>

using namespace std;

void part1() {
    ifstream input("input/input01");
    char first = input.get();
    char prev  = first;

    uint32_t res = 0;

    for (char c = input.get(); c != '\n' && c != '\r'; c = input.get()) {
        if (c == prev) {
            res += prev - '0';
        }
        prev = c;
    }
    if (prev == first) {
        res += prev - '0';
    }
    println("{}", res);
}

void part2() {
    ifstream input("input/input01");
    string line;
    getline(input, line);

    uint res = 0;
    for (auto it = line.begin(), jt = line.begin() + line.size() / 2; jt != line.end(); ++it, ++jt) {
        if (*it == *jt) {
            res += (*it - '0') * 2;
        }
    }
    println("{}", res);
}

int main() {
    part1();
    part2();
    return 0;
}
