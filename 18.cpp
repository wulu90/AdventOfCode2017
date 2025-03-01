#include <charconv>
#include <fstream>
#include <map>
#include <queue>
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

void run(const vector<string>& ins_vec, map<char, int64_t>& regs, size_t& off, queue<int64_t>& s_q, queue<int64_t>& r_q,
         int64_t& snd_count) {
    while (off < ins_vec.size()) {
        auto& ins = ins_vec[off];
        if (ins.starts_with("snd")) {
            s_q.push(get_x(ins, regs));
            ++snd_count;
            ++off;
        } else if (ins.starts_with("rcv")) {
            if (r_q.empty()) {
                break;
            } else {
                regs[ins[4]] = r_q.front();
                r_q.pop();
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

void part2() {
    ifstream input("input/input18");
    vector<string> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(line);
    }

    map<char, int64_t> regs0, regs1;
    regs0['p'] = 0;
    regs1['p'] = 1;

    size_t off0 = 0;
    size_t off1 = 0;

    queue<int64_t> q0;
    queue<int64_t> q1;
    int64_t snd_count0 = 0;
    int64_t snd_count1 = 0;

    while (true) {
        run(ins_vec, regs0, off0, q1, q0, snd_count0);
        run(ins_vec, regs1, off1, q0, q1, snd_count1);

        if (q0.empty() && q1.empty()) {
            println("{},{}", snd_count0, snd_count1);
            break;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
