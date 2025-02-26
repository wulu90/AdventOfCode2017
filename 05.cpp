#include <fstream>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input/input05");
    vector<int> off_vec;
    for (int num; input >> num;) {
        off_vec.push_back(num);
    }

    size_t i    = 0;
    size_t step = 0;
    while (i < off_vec.size()) {
        auto tmp = i;
        i += off_vec[i];
        ++off_vec[tmp];
        ++step;
    }
    println("{}", step);
}

void part2() {
    ifstream input("input/input05");
    vector<int> off_vec;
    for (int num; input >> num;) {
        off_vec.push_back(num);
    }

    size_t i    = 0;
    size_t step = 0;
    while (i < off_vec.size()) {
        auto tmp = i;
        i += off_vec[i];
        off_vec[tmp] += off_vec[tmp] >= 3 ? -1 : 1;
        ++step;
    }
    println("{}", step);
}

int main() {
    part1();
    part2();
    return 0;
}
