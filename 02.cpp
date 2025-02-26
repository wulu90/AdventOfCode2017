#include <fstream>

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

int main() {
    part1();
    return 0;
}
