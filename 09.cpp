#include <fstream>
#include <stack>

using namespace std;

void part1() {
    ifstream input("input/input09");
    int score = 0;
    stack<int> s;
    bool garbge = false;
    for (char c = input.get(); c != '\r' && c != '\n'; c = input.get()) {
        if (c == '{' && !garbge) {
            s.push(s.empty() ? 1 : s.top() + 1);
        } else if (c == '}' && !garbge) {
            score += s.top();
            s.pop();
        } else if (c == '<' && !garbge) {
            garbge = true;
        } else if (c == '>' && garbge) {
            garbge = false;
        } else if (c == '!') {
            input.get();
        }
    }

    println("{}", score);
}

int main() {
    part1();
    return 0;
}
