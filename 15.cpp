#include <charconv>
#include <fstream>

using namespace std;

int64_t parse(const string& line) {
    auto pos    = line.rfind(' ');
    int64_t num = 0;
    from_chars(line.data() + pos + 1, line.data() + line.size(), num);
    return num;
}

bool compare_lowest_16bits(uint64_t a, uint64_t b) {
    return (a & 0xFFFFUL) == (b & 0xFFFFUL);
}

void part1() {
    ifstream input("input/input15");
    string line;
    getline(input, line);
    int64_t gen_A = parse(line);

    getline(input, line);
    int64_t gen_B = parse(line);

    int judge_count = 0;

    for (size_t i = 0; i < 40'000'000; ++i) {
        gen_A = (gen_A * 16807) % 2147483647;
        gen_B = (gen_B * 48271) % 2147483647;
        if (compare_lowest_16bits(gen_A, gen_B)) {
            ++judge_count;
        }
    }

    println("{}", judge_count);
}

int main() {
    part1();
    return 0;
}
