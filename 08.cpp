#include <charconv>
#include <fstream>
#include <functional>
#include <map>
#include <ranges>
#include <string>
#include <string_view>

using namespace std;
using instruction = tuple<string, function<int(int, int)>, int, string, function<bool(int, int)>, int>;

instruction parse(const string& str) {
    auto sp_v    = str | views::split(' ');
    auto sp_v_it = sp_v.begin();
    string_view reg_modify{*sp_v_it};
    ++sp_v_it;
    string_view inc_dec{*sp_v_it};
    function<int(int, int)> func =
        inc_dec == "inc"sv ? function<int(int, int)>(plus<int>()) : static_cast<function<int(int, int)>>(minus<int>());

    ++sp_v_it;
    string_view amout_sv{*sp_v_it};
    int amount = 0;
    from_chars(amout_sv.begin(), amout_sv.end(), amount);
    ++sp_v_it;
    ++sp_v_it;
    string_view reg_condition{*sp_v_it};
    ++sp_v_it;
    string_view comp{*sp_v_it};
    function<bool(int, int)> func_comp;
    if (comp == ">") {
        func_comp = greater<>();
    } else if (comp == ">=") {
        func_comp = greater_equal<>();
    } else if (comp == "<") {
        func_comp = less<>();
    } else if (comp == "<=") {
        func_comp = less_equal<>();
    } else if (comp == "==") {
        func_comp = equal_to<>();
    } else {
        func_comp = not_equal_to<>();
    }
    ++sp_v_it;
    int num_comp = 0;
    string_view num_comp_sv{*sp_v_it};
    from_chars(num_comp_sv.begin(), num_comp_sv.end(), num_comp);

    return {string{reg_modify}, func, amount, string{reg_condition}, func_comp, num_comp};
}

void part1() {
    ifstream input("input/input08");
    map<string, int> reg_map;
    int highest = INT32_MIN;
    for (string line; getline(input, line);) {
        auto [reg_m, func_m, amount, reg_c, func_c, num_c] = parse(line);    // modify,compare
        if (func_c(reg_map[reg_c], num_c)) {
            reg_map[reg_m] = func_m(reg_map[reg_m], amount);
            highest        = max(highest, reg_map[reg_m]);
        }
    }

    auto vv = reg_map | views::values;
    println("{}", *max_element(vv.begin(), vv.end()));
    println("{}", highest);
}

int main() {
    part1();
    return 0;
}
