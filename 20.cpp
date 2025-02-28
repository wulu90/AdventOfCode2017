#include <fstream>
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

int main() {
    part1();
    return 0;
}
