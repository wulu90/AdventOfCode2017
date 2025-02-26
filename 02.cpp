#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input/input02");
    int largest  = INT32_MIN;
    int smallest = INT32_MAX;
    int checksum = 0;
    int num      = 0;
    while (input >> num) {
        if (num > largest) {
            largest = num;
        }
        if (num < smallest) {
            smallest = num;
        }

        if (input.peek() == '\r' || input.peek() == '\n') {
            checksum += largest - smallest;
            largest  = INT32_MIN;
            smallest = INT32_MAX;
        }
    }

    println("{}", checksum);
}

void part2() {
    ifstream input("input/input02");
    vector<int> row_vec;
    int num        = 0;
    int result_sum = 0;
    while (input >> num) {
        row_vec.push_back(num);

        if (input.peek() == '\r' || input.peek() == '\n') {
            sort(row_vec.begin(), row_vec.end(), greater<int>());
            bool divide_evenly = false;
            for (size_t i = 0; i < row_vec.size() - 1; ++i) {
                for (size_t j = i + 1; j < row_vec.size(); ++j) {
                    if (row_vec[i] % row_vec[j] == 0) {
                        result_sum += row_vec[i] / row_vec[j];
                        divide_evenly = true;
                        break;
                    }
                }
                if (divide_evenly) {
                    break;
                }
            }
            row_vec.clear();
        }
    }

    println("{}", result_sum);
}

int main() {
    part1();
    part2();
    return 0;
}
