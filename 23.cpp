#include <charconv>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int get_y(const string& str, const array<int, 8>& regs) {
    int num = 0;
    if (isalpha(str[6])) {
        num = regs[str[6] - 'a'];
    } else {
        auto p = str.rfind(' ');
        from_chars(str.data() + p + 1, str.data() + str.size(), num);
    }
    return num;
}

void setxy(const string& str, array<int, 8>& regs) {
    regs[str[4] - 'a'] = get_y(str, regs);
}

void subxy(const string& str, array<int, 8>& regs) {
    regs[str[4] - 'a'] -= get_y(str, regs);
}

void mulxy(const string& str, array<int, 8>& regs) {
    regs[str[4] - 'a'] = regs[str[4] - 'a'] * get_y(str, regs);
}

void part1() {
    ifstream input("input/input23");
    vector<string> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(line);
    }
    array<int, 8> regs;
    regs.fill(0);
    size_t off       = 0;
    size_t mul_count = 0;
    while (off < ins_vec.size()) {
        auto& ins = ins_vec[off];
        if (ins.starts_with("mul")) {
            mulxy(ins, regs);
            ++mul_count;
            ++off;
        } else if (ins.starts_with("set")) {
            setxy(ins, regs);
            ++off;
        } else if (ins.starts_with("sub")) {
            subxy(ins, regs);
            ++off;
        } else {    // jnz
            int num = 0;
            if (isalpha(ins[4])) {
                num = regs[ins[4] - 'a'];
            } else {
                auto p = ins.rfind(' ');
                from_chars(ins.data() + 4, ins.data() + p, num);
            }
            if (num != 0) {
                off += get_y(ins, regs);
            } else {
                ++off;
            }
        }
    }

    println("{}", mul_count);
}

int main() {
    part1();
    return 0;
}
