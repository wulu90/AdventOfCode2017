#include <charconv>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int64_t get_y(const string& str, const array<int64_t, 8>& regs) {
    int64_t num = 0;
    if (isalpha(str[6])) {
        num = regs[str[6] - 'a'];
    } else {
        auto p = str.rfind(' ');
        from_chars(str.data() + p + 1, str.data() + str.size(), num);
    }
    return num;
}

void setxy(const string& str, array<int64_t, 8>& regs) {
    regs[str[4] - 'a'] = get_y(str, regs);
}

void subxy(const string& str, array<int64_t, 8>& regs) {
    regs[str[4] - 'a'] -= get_y(str, regs);
}

void mulxy(const string& str, array<int64_t, 8>& regs) {
    regs[str[4] - 'a'] = regs[str[4] - 'a'] * get_y(str, regs);
}

void part1() {
    ifstream input("input/input23");
    vector<string> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(line);
    }
    array<int64_t, 8> regs;
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
            int64_t num = 0;
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

void part2() {
    ifstream input("../input/input23");
    vector<string> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(line);
    }
    array<int64_t, 8> regs{1, 0, 0, 0, 0, 0, 0, 0};
    size_t off = 0;
    while (off < ins_vec.size()) {
        auto& ins = ins_vec[off];
        if (ins.starts_with("mul")) {
            mulxy(ins, regs);
            ++off;
        } else if (ins.starts_with("set")) {
            setxy(ins, regs);
            ++off;
        } else if (ins.starts_with("sub")) {
            subxy(ins, regs);
            ++off;
        } else {    // jnz
            int64_t num = 0;
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

    println("{}", regs);
}

/**
void part2_1() {
    int a = 1;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int g = 0;
    int h = 0;

    b = 93;
    c = b;
    b *= 100;
    b += 100000;
    c = b;
    c += 17000;

    do {
        f = 1;
        d = 2;

        do {
            e = 2;
            do {
                g = d;
                g *= e;
                g -= b;
                if (g == 0) {
                    f = 0;
                }
                e += 1;
                g = e;
                g -= b;
            } while (g != 0);
            d += 1;
            g = d;
            g -= b;

        } while (g != 0);

        if (f == 0) {
            h += 1;
            println("{},{},{},{},{},{},{},{}", a, b, c, d, e, f, g, h);
        }
        g = b;
        g -= c;
        if (g == 0) {
            break;
        }
        b += 17;
    } while (true);
    println("{}", h);
}
*/
bool is_prime(int num) {
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void part2_2() {
    int h = 0;
    for (int i = 109300; i <= 126300; i += 17) {
        if (!is_prime(i)) {
            ++h;
            // println("{},{}", i, h);
        }
    }
    println("{}", h);
}

int main() {
    part1();
    part2_2();
    return 0;
}
