#include <algorithm>
#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using namespace std;

array<int, 9> parse(const string& str) {
    static const regex patter{R"((-?\d+))"};
    array<int, 9> pva;
    size_t i = 0;
    for (sregex_iterator it(str.begin(), str.end(), patter); it != sregex_iterator(); ++it) {
        pva[i++] = stoi(it->str());
    }
    return pva;
}

void part1() {
    ifstream input("input/input20");
    vector<array<int, 9>> pva_vec;
    for (string line; getline(input, line);) {
        pva_vec.push_back(parse(line));
    }

    /*
    y=a*x^2+b*x+c min_max value c-(b^2)/4a
    position,velocity,acceleartion,time, a acceleration, t time, x start position
    (1/2)*a*t^2+v*t+x
    x-(v^2)/(2a)
    */

    vector<int> dist_vec;
    for (auto& pva : pva_vec) {
        int dist = 0;
        for (size_t i = 0; i < 3; ++i) {
            if (pva[i + 6] == 0) {
                if (pva[i] * pva[i + 3] > 0) {
                    dist += abs(pva[i]);
                } else {
                    dist += 0;
                }
            } else {
                dist += abs(pva[i] - (pva[i + 3] * pva[i + 3]) / (2 * pva[i + 6]));
            }
        }
        dist_vec.push_back(dist);
    }

    println("{}", min_element(dist_vec.begin(), dist_vec.end()) - dist_vec.begin());
}

void step(array<int, 9>& pva) {
    pva[3] += pva[6];
    pva[4] += pva[7];
    pva[5] += pva[8];
    pva[0] += pva[3];
    pva[1] += pva[4];
    pva[2] += pva[5];
}

bool collide(const array<int, 9>& lhs, const array<int, 9>& rhs) {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
}

vector<size_t> check_all(const vector<array<int, 9>>& pva_vec) {
    map<array<int, 3>, vector<size_t>> pos_index;
    for (size_t i = 0; i < pva_vec.size(); ++i) {
        pos_index[{pva_vec[i][0], pva_vec[i][1], pva_vec[i][2]}].push_back(i);
    }
    vector<size_t> res;
    for (auto [_, vec] : pos_index) {
        if (vec.size() > 1) {
            res.append_range(vec);
        }
    }
    sort(res.begin(), res.end(), greater<>());
    return res;
}

void part2() {
    ifstream input("input/input20");
    vector<array<int, 9>> pva_vec;
    for (string line; getline(input, line);) {
        pva_vec.push_back(parse(line));
    }

    for (size_t i = 0; i < 1000; ++i) {
        for (auto& pva : pva_vec) {
            step(pva);
        }

        auto coll_vec = check_all(pva_vec);
        // if (coll_vec.size() > 0) {
        //     println("{},{},{}", i, coll_vec, pva_vec.size() - coll_vec.size());
        // }
        // 38 is enough,
        for (auto inx : coll_vec) {
            pva_vec.erase(pva_vec.begin() + inx);
        }
    }

    println("{}", pva_vec.size());
}

int main() {
    part1();
    part2();
    return 0;
}
