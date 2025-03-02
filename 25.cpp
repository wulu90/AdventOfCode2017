#include <map>
#include <print>

using namespace std;

int main() {
    int cursor = 0;
    map<int, int> slot_value;
    int state      = 0;    // ABCDEF 012345
    int curr_value = 0;
    for (int i = 0; i < 12386363; ++i) {
        curr_value = slot_value[cursor];

        switch (state) {
        case 0:    // A
            slot_value[cursor] = curr_value == 0 ? 1 : 0;
            cursor             = curr_value == 0 ? cursor + 1 : cursor - 1;
            state              = curr_value == 0 ? 1 : 4;    // B:E
            break;
        case 1:    // B
            slot_value[cursor] = curr_value == 0 ? 1 : 0;
            cursor             = curr_value == 0 ? cursor - 1 : cursor + 1;
            state              = curr_value == 0 ? 2 : 0;    // C:A
            break;
        case 2:    // C
            slot_value[cursor] = curr_value == 0 ? 1 : 0;
            cursor             = curr_value == 0 ? cursor - 1 : cursor + 1;
            state              = curr_value == 0 ? 3 : 2;    // D:C
            break;
        case 3:    // D
            slot_value[cursor] = curr_value == 0 ? 1 : 0;
            cursor             = cursor - 1;
            state              = curr_value == 0 ? 4 : 5;    // E:F
            break;
        case 4:    // E
            slot_value[cursor] = curr_value == 0 ? 1 : 1;
            cursor             = cursor - 1;
            state              = curr_value == 0 ? 0 : 2;    // A:C
            break;
        case 5:    // E
            slot_value[cursor] = curr_value == 0 ? 1 : 1;
            cursor             = curr_value == 0 ? cursor - 1 : cursor + 1;
            state              = curr_value == 0 ? 4 : 0;    // E:A
            break;
        }
    }

    int checksum = 0;
    for (auto [_, v] : slot_value) {
        if (v == 1) {
            ++checksum;
        }
    }
    println("{}", checksum);
}
