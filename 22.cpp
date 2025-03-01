#include <fstream>
#include <set>
#include <string>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input/input22");
    vector<string> infection_status;
    for (string line; getline(input, line);) {
        infection_status.push_back(line);
    }

    int row_count = infection_status.size();
    int col_count = infection_status.front().size();
    set<pair<int, int>> infected;
    for (int i = 0; i < row_count; ++i) {
        for (int j = 0; j < col_count; ++j) {
            if (infection_status[i][j] == '#') {
                infected.insert({i - row_count / 2, j - col_count / 2});
            }
        }
    }

    pair<int, int> curr_coord{0, 0};
    int curr_facing     = 0;
    int cause_infection = 0;
    static const array<array<int, 2>, 4> deltas{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
    for (int i = 0; i < 10000; ++i) {
        if (infected.contains(curr_coord)) {    // infected
            curr_facing = curr_facing == 3 ? 0 : curr_facing + 1;
            infected.erase(curr_coord);
        } else {
            curr_facing = curr_facing == 0 ? 3 : curr_facing - 1;
            infected.insert(curr_coord);
            ++cause_infection;
        }
        curr_coord = make_pair(curr_coord.first + deltas[curr_facing][0], curr_coord.second + deltas[curr_facing][1]);
    }

    println("{}", cause_infection);
}

int main() {
    part1();
    return 0;
}
