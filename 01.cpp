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

int main() {
    part1();
    return 0;
}
