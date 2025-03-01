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
    size_t curr_facing  = 0;
    int cause_infection = 0;
    static const array<array<int, 2>, 4> deltas{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
    for (int i = 0; i < 10000; ++i) {
        if (infected.contains(curr_coord)) {    // infected
            curr_facing = (curr_facing + 1) % 4;
            infected.erase(curr_coord);
        } else {
            curr_facing = (curr_facing - 1) % 4;
            infected.insert(curr_coord);
            ++cause_infection;
        }
        curr_coord = make_pair(curr_coord.first + deltas[curr_facing][0], curr_coord.second + deltas[curr_facing][1]);
    }

    println("{}", cause_infection);
}

void part2() {
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
    set<pair<int, int>> weakened;
    set<pair<int, int>> flagged;

    pair<int, int> curr_coord{0, 0};
    size_t curr_facing  = 0;
    int cause_infection = 0;
    static const array<array<int, 2>, 4> deltas{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
    for (int i = 0; i < 10000000; ++i) {
        if (infected.contains(curr_coord)) {    // infected
            curr_facing = (curr_facing + 1) % 4;
            infected.erase(curr_coord);
            flagged.insert(curr_coord);
        } else if (weakened.contains(curr_coord)) {
            weakened.erase(curr_coord);
            infected.insert(curr_coord);
            ++cause_infection;
        } else if (flagged.contains(curr_coord)) {
            curr_facing = (curr_facing + 2) % 4;
            flagged.erase(curr_coord);
        } else {
            curr_facing = (curr_facing - 1) % 4;
            weakened.insert(curr_coord);
        }
        curr_coord = make_pair(curr_coord.first + deltas[curr_facing][0], curr_coord.second + deltas[curr_facing][1]);
    }

    println("{}", cause_infection);
}

int main() {
    part1();
    part2();
    return 0;
}
