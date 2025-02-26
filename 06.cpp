#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

void part1() {
    ifstream input("input/input06");
    static const size_t banksize = 16;
    array<int, banksize> mem_banks;
    for (size_t i = 0; i < banksize; ++i) {
        input >> mem_banks[i];
    }

    set<array<int, banksize>> seen;
    seen.insert(mem_banks);
    int step = 0;
    while (true) {
        auto max_it    = max_element(mem_banks.begin(), mem_banks.end());
        auto max_value = *max_it;
        *max_it        = 0;
        for_each(mem_banks.begin(), mem_banks.end(), [&max_it, max_value](auto& mem) { return mem += max_value / banksize; });
        auto mod     = max_value % banksize;
        auto next_it = next(max_it, 1);
        if (next_it == mem_banks.end()) {
            next_it = mem_banks.begin();
        }
        for_each_n(next_it, mod > mem_banks.end() - next_it ? mem_banks.end() - next_it : mod, [](auto& mem) { return ++mem; });
        if (mod > mem_banks.end() - next_it) {
            for_each_n(mem_banks.begin(), mod - (mem_banks.end() - next_it), [](auto& mem) { return ++mem; });
        }

        // println("{}", mem_banks);
        ++step;

        if (!seen.contains(mem_banks)) {
            seen.insert(mem_banks);
        } else {
            println("{}", step);
            break;
        }
    }
}

int main() {
    part1();
    return 0;
}
