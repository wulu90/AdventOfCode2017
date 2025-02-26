#include <charconv>
#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

struct program {
    int weight;
    program* parent;
    vector<program*> children;
    int child_weight_sum;
};

void parse(const string& str, map<string, program*>& prog_map) {
    auto sp_v    = str | views::split(" -> "sv);
    auto sp_v_it = sp_v.begin();

    auto lhs_sp_v = string_view(*sp_v_it) | views::split(' ');
    auto lhs_it   = lhs_sp_v.begin();

    string_view name_sv{*lhs_it};
    ++lhs_it;
    string_view weight_sv{*lhs_it};

    ++sp_v_it;
    vector<string_view> children_sv;
    if (sp_v_it != sp_v.end()) {
        children_sv = string_view(*sp_v_it) | views::split(", "sv) | views::transform([](auto&& it) { return string_view{it}; }) |
                      ranges::to<vector>();
    }

    if (!prog_map.contains(string{name_sv})) {
        program* p          = new program;
        p->parent           = nullptr;
        p->child_weight_sum = 0;    // !!!
        p->weight           = 0;    // !!!
        from_chars(weight_sv.begin() + 1, weight_sv.end() - 1, p->weight);
        prog_map.insert({string{name_sv}, p});
    } else {
        from_chars(weight_sv.begin() + 1, weight_sv.end() - 1, prog_map.at(string{name_sv})->weight);
    }

    if (!children_sv.empty()) {
        for (auto sv : children_sv) {
            if (!prog_map.contains(string{sv})) {
                program* p          = new program;
                p->parent           = prog_map.at(string{name_sv});
                p->child_weight_sum = 0;    // !!!
                p->weight           = 0;    // !!!
                prog_map.insert({string{sv}, p});
            } else {
                prog_map.at(string{sv})->parent = prog_map.at(string{name_sv});
            }
            prog_map.at(string{name_sv})->children.push_back(prog_map.at(string{sv}));
        }
    }
}

void calc_sub_weight(program* parent) {
    if (!parent->children.empty()) {
        for (auto child : parent->children) {
            calc_sub_weight(child);
            parent->child_weight_sum += child->child_weight_sum + child->weight;
        }
    }
}

program* find_unblanced(program* parent) {
    program* unb = parent;
    map<int, vector<program*>> wei_map;
    for (auto child : parent->children) {
        wei_map[child->weight + child->child_weight_sum].push_back(child);
    }

    if (wei_map.size() != 1) {
        auto p = wei_map.begin()->second.size() == 1 ? wei_map.begin()->second.front() : wei_map.rbegin()->second.front();
        unb    = find_unblanced(p);
    }
    return unb;
}

void part1_2() {
    ifstream input("input/input07");
    map<string, program*> prog_map;

    for (string line; getline(input, line);) {
        parse(line, prog_map);
    }

    program* root = nullptr;
    for (auto [name, p] : prog_map) {
        if (p->parent == nullptr) {
            println("{}", name);
            root = p;
            break;
        }
    }

    calc_sub_weight(root);

    auto unb = find_unblanced(root);

    int b_weight = 0;
    for (auto p : unb->parent->children) {
        if (p != unb) {
            b_weight = p->child_weight_sum + p->weight;
            break;
        }
    }

    println("{}", b_weight - unb->child_weight_sum);

    for (auto [name, p] : prog_map) {
        if (p != nullptr) {
            delete p;
        }
    }
}

int main() {
    part1_2();
    return 0;
}
