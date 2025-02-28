#include <charconv>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int64_t get_x(const string& str, map<char, int64_t>& regs) {
    int64_t num = 0;
    auto pos    = str.find(' ');
    if (isalpha(str[pos + 1])) {
        num = regs[str[pos + 1]];
    } else {
        from_chars(str.data() + pos + 1, str.data() + str.size(), num);
    }
    return num;
}

int64_t get_y(const string& str, map<char, int64_t>& regs) {
    int64_t num = 0;
    auto pos    = str.rfind(' ');
    if (isalpha(str[pos + 1])) {
        num = regs[str[pos + 1]];
    } else {
        from_chars(str.data() + pos + 1, str.data() + str.size(), num);
    }
    return num;
}

void set_add_mul_mod(const string& str, map<char, int64_t>& regs) {
    int64_t num = get_y(str, regs);
    if (str.starts_with("set")) {
        regs[str[4]] = num;
    } else if (str.starts_with("add")) {
        regs[str[4]] += num;
    } else if (str.starts_with("mul")) {
        regs[str[4]] *= num;
    } else if (str.starts_with("mod")) {
        regs[str[4]] %= num;
    }
}

void part1() {
    ifstream input("input/input18");
    vector<string> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(line);
    }

    map<char, int64_t> regs;

    size_t off        = 0;
    int64_t frequency = 0;
    while (off < ins_vec.size()) {
        auto& ins = ins_vec[off];
        if (ins.starts_with("snd")) {
            frequency = get_x(ins, regs);
            ++off;
        } else if (ins.starts_with("rcv")) {
            if (get_x(ins, regs) != 0) {
                println("{}", frequency);
                break;
            } else {
                ++off;
            }
        } else if (ins.starts_with("jgz")) {
            if (get_x(ins, regs) > 0) {
                off += get_y(ins, regs);
            } else {
                ++off;
            }
        } else {
            set_add_mul_mod(ins, regs);
            ++off;
        }
    }
}

int main() {
    part1();
    return 0;
}
