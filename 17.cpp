#include <print>
#include <vector>
using namespace std;

void part1() {
    static const int input = 304;
    vector<int> buffer;
    buffer.reserve(2018);
    buffer.push_back(0);
    size_t pos = 0;
    for (int i = 1; i <= 2017; ++i) {
        pos = (pos + input) % i + 1;

        if (pos == i) {
            buffer.push_back(i);
        } else {
            buffer.insert(buffer.begin() + pos, i);
        }
    }
    println("{}", buffer[pos + 1]);
}

void part2() {
    static const int input = 304;

    size_t pos     = 0;
    int after_zero = 0;
    for (int i = 1; i <= 5000'0000; ++i) {
        pos = (pos + input) % i + 1;
        if (pos == 1) {
            after_zero = i;
        }
    }

    println("{}", after_zero);
}

int main() {
    part1();
    part2();
    return 0;
}
