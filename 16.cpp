#include <algorithm>
#include <charconv>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

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

void spin2(string& str, size_t x, size_t b = 0) {
    rotate(str.rbegin(), str.rbegin() + x, str.rend());
}

void exc2(string& str, size_t a, size_t b) {
    swap(str[a], str[b]);
}

void par2(string& str, size_t a, size_t b) {
    auto p1 = str.find(static_cast<char>(a));
    auto p2 = str.find(static_cast<char>(b));
    exc2(str, p1, p2);
}

void part2() {
    ifstream input("input/input16");
    string programs{"abcdefghijklmnop"};
    vector<pair<function<void(string&, size_t, size_t)>, pair<size_t, size_t>>> dance_move_vec;
    for (string line; getline(input, line, ',');) {
        if (line.back() == '\n' || line.back() == '\r') {
            line.pop_back();
        }

        if (line[0] == 's') {
            dance_move_vec.push_back({&spin2, {parse_spin_num(line), 0}});
        } else if (line[0] == 'x') {
            dance_move_vec.push_back({&exc2, parse_exc_pos(line)});
        } else {
            dance_move_vec.push_back({&par2, {line[1], line[3]}});
        }
    }

    for (size_t i = 0; i < 1'000'000'000 * dance_move_vec.size(); ++i) {
        auto [func, argv] = dance_move_vec[i % dance_move_vec.size()];
        func(programs, argv.first, argv.second);
        if (programs == "abcdefghijklmnop") {
            i = 1'000'000'000 * dance_move_vec.size() - 1 - (1'000'000'000 * dance_move_vec.size()) % (i + 1);
        }
    }

    println("{}", programs);
}

int main() {
    part1();
    part2();
    return 0;
}
