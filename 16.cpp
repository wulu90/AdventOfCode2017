#include <algorithm>
#include <charconv>
#include <fstream>
#include <string>

using namespace std;

void spin(string& str, size_t x) {
    rotate(str.rbegin(), str.rbegin() + x, str.rend());
}

void exc(string& str, pair<size_t, size_t> poss) {
    swap(str[poss.first], str[poss.second]);
}

void par(string& str, char a, char b) {
    auto p1 = str.find(a);
    auto p2 = str.find(b);
    exc(str, {p1, p2});
}

pair<size_t, size_t> parse_exc_pos(const string& str) {
    auto slash = str.find('/');
    size_t a   = 0;
    size_t b   = 0;
    from_chars(str.data() + 1, str.data() + slash, a);
    from_chars(str.data() + slash + 1, str.data() + str.size(), b);
    return {a, b};
}

size_t parse_spin_num(const string& str) {
    size_t x = 0;
    from_chars(str.data() + 1, str.data() + str.size(), x);
    return x;
}

void part1() {
    ifstream input("input/input16");
    string programs{"abcdefghijklmnop"};
    for (string line; getline(input, line, ',');) {
        if (line.back() == '\n' || line.back() == '\r') {
            line.pop_back();
        }

        if (line[0] == 's') {
            spin(programs, parse_spin_num(line));
        } else if (line[0] == 'x') {
            exc(programs, parse_exc_pos(line));
        } else {
            par(programs, line[1], line[3]);
        }
    }

    println("{}", programs);
}

int main() {
    part1();
    return 0;
}
