#include <fstream>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

pair<string, string> parse(const string& str) {
    auto sp_v = str | views::split(" => "sv);
    auto it   = sp_v.begin();
    string_view lhs{*it};
    ++it;
    string_view rhs{*it};

    string lstr;
    for (auto c : lhs) {
        if (c != '/') {
            lstr.push_back(c);
        }
    }
    string rstr;
    for (auto c : rhs) {
        if (c != '/') {
            rstr.push_back(c);
        }
    }
    return {lstr, rstr};
}

vector<string> rotate_flip_2(const string& str) {
    /// 01
    /// 23 => 01/23
    /// 23/01, 10/32
    /// 20/31, 32/10, 13/02, 01/23

    string str1{str[3], str[4], '/', str[0], str[1]};
    string str2{str[1], str[0], '/', str[4], str[3]};
    string str3{str[3], str[0], '/', str[4], str[1]};
    string str4{str[4], str[3], '/', str[1], str[0]};
    string str5{str[1], str[4], '/', str[0], str[3]};
    return {str1, str2, str3, str4, str5};
}

vector<string> rotate_flip_2_s(const string& str) {
    /// 01
    /// 23 => 01/23
    /// 23/01, 10/32
    /// 20/31, 32/10, 13/02, 01/23

    string str1{str[2], str[3], str[0], str[1]};
    string str2{str[1], str[0], str[3], str[2]};
    string str3{str[2], str[0], str[3], str[1]};
    string str4{str[3], str[2], str[1], str[0]};
    string str5{str[1], str[3], str[0], str[2]};
    return {str1, str2, str3, str4, str5};
}

vector<string> rotate_flip_3(const string& str) {
    /// 012/
    /// 345/
    /// 678 => 012/345/678
    /// 678/345/012 210/543/876
    /// 630/741/852 876/543/210 258/147/036

    string str1{str[8], str[9], str[10], '/', str[4], str[5], str[6], '/', str[0], str[1], str[2]};
    string str2{str[2], str[1], str[0], '/', str[6], str[5], str[4], '/', str[10], str[9], str[8]};
    string str3{str[8], str[4], str[0], '/', str[9], str[5], str[1], '/', str[10], str[6], str[2]};
    string str4{str[10], str[9], str[8], '/', str[6], str[5], str[4], '/', str[2], str[1], str[0]};
    string str5{str[2], str[6], str[10], '/', str[1], str[5], str[9], '/', str[0], str[4], str[8]};
    return {str1, str2, str3, str4, str5};
}

vector<string> rotate_flip_3_s(const string& str) {
    /// 012/
    /// 345/
    /// 678 => 012/345/678
    /// 678/345/012 210/543/876
    /// 630/741/852 876/543/210 258/147/036

    string str1{str[6], str[7], str[8], str[3], str[4], str[5], str[0], str[1], str[2]};
    string str2{str[2], str[1], str[0], str[5], str[4], str[3], str[8], str[7], str[6]};
    string str3{str[6], str[3], str[0], str[7], str[4], str[1], str[8], str[5], str[2]};
    string str4{str[8], str[7], str[6], str[5], str[4], str[3], str[2], str[1], str[0]};
    string str5{str[2], str[5], str[8], str[1], str[4], str[7], str[0], str[3], str[6]};
    return {str1, str2, str3, str4, str5};
}

void part1() {
    ifstream input("input/input21");
    map<string, string> rules;
    for (string line; getline(input, line);) {
        auto [s1, s2] = parse(line);
        rules.insert({s1, s2});
        auto strvec = s1.size() == 4 ? rotate_flip_2_s(s1) : rotate_flip_3_s(s1);
        for (auto& s : strvec) {
            rules.insert({s, s2});
        }
    }

    vector<string> image{".#.", "..#", "###"};
    size_t side = 3;

    for (int i = 0; i < 5; ++i) {
        if (side % 2 == 0) {
            size_t n = side / 2;
            side     = n * 3;

            string row(side, ' ');
            vector<string> img(side, row);

            for (size_t j = 0; j < n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    string pattern{image[j * 2][k * 2], image[j * 2][k * 2 + 1], image[j * 2 + 1][k * 2], image[j * 2 + 1][k * 2 + 1]};
                    string rpl;
                    for (auto s : rotate_flip_2_s(pattern)) {
                        if (rules.contains(s)) {
                            rpl = rules[s];
                            break;
                        }
                    }

                    for (size_t x = 0; x < 3; ++x) {
                        for (size_t y = 0; y < 3; ++y) {
                            img[j * 3 + x][k * 3 + y] = rpl[x * 3 + y];
                        }
                    }
                }
            }
            image = std::move(img);
        } else {
            size_t n = side / 3;
            side     = n * 4;
            string row(side, ' ');
            vector<string> img(side, row);

            for (size_t j = 0; j < n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    string pattern;
                    for (size_t x = 0; x < 3; ++x) {
                        for (size_t y = 0; y < 3; ++y) {
                            pattern.push_back(image[j * 3 + x][k * 3 + y]);
                        }
                    }

                    string rpl;
                    for (auto s : rotate_flip_3_s(pattern)) {
                        if (rules.contains(s)) {
                            rpl = rules[s];
                            break;
                        }
                    }

                    for (size_t x = 0; x < 4; ++x) {
                        for (size_t y = 0; y < 4; ++y) {
                            img[j * 4 + x][k * 4 + y] = rpl[x * 4 + y];
                        }
                    }
                }
            }
            image = std::move(img);
        }
    }

    size_t on_count = 0;
    for (auto& row : image) {
        for (auto c : row) {
            if (c == '#') {
                ++on_count;
            }
        }
    }

    println("{}", on_count);
}

int main() {
    part1();
    return 0;
}
