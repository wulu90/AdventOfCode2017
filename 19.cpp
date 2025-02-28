#include <fstream>
#include <string>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input/input19");
    vector<string> routing_diagram;
    for (string line; getline(input, line);) {
        routing_diagram.push_back(line);
    }
    string path;
    int step = 0;
    static const array<array<int, 2>, 4> direction{{{1, 0}, {0, -1}, {-1, 0}, {0, 1}}};
    size_t curr_dire = 0;

    auto pos = routing_diagram.front().find('|');
    size_t r = 0;
    size_t c = pos;
    while (true) {
        while (routing_diagram[r][c] != ' ') {
            ++step;
            if (isalpha(routing_diagram[r][c])) {
                path.push_back(routing_diagram[r][c]);
            }
            r = r + direction[curr_dire][0];
            c = c + direction[curr_dire][1];
            if (routing_diagram[r][c] == '+') {
                break;
            }
        }
        // println("{},{},{},{}", r, c, curr_dire, path);
        bool end      = true;
        size_t n_dire = curr_dire == 3 ? 0 : curr_dire + 1;
        auto n_r      = r + direction[n_dire][0];
        auto n_c      = c + direction[n_dire][1];
        if (n_r < routing_diagram.size() && n_c < routing_diagram.front().size() && routing_diagram[n_r][n_c] != ' ') {
            end       = false;
            curr_dire = n_dire;
            r         = n_r;
            c         = n_c;
            ++step;
        }

        if (end) {
            n_dire   = curr_dire == 0 ? 3 : curr_dire - 1;
            auto n_r = r + direction[n_dire][0];
            auto n_c = c + direction[n_dire][1];
            if (n_r < routing_diagram.size() && n_c < routing_diagram.front().size() && routing_diagram[n_r][n_c] != ' ') {
                end       = false;
                curr_dire = n_dire;
                r         = n_r;
                c         = n_c;
                ++step;
            }
        }

        if (end) {
            break;
        }
    }

    println("{}", path);
    println("{}", step);
}

int main() {
    part1();
    return 0;
}
