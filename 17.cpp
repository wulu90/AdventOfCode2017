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
        pos = (pos + input) % i;
        if (pos == i - 1) {
            buffer.push_back(i);
            pos = i;
        } else {
            pos += 1;
            buffer.insert(buffer.begin() + pos, i);
        }
    }
    println("{}", buffer[pos + 1]);
}

int main() {
    part1();
    return 0;
}
