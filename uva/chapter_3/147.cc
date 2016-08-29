#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
using llu = unsigned long long;

const int MAX = 30000 / 5;

int main() {
    int coins[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
    for (auto &c : coins) c /= 5;

    llu ways[MAX + 1];
    fill_n(ways, MAX + 1, 0);
    ways[0] = 1;
    for (int c : coins) {
        for (int i = MAX; i > 0; i--) {
            int j = c;
            while (i - j >= 0) {
                ways[i] += ways[i - j];
                j += c;
            }
        }
    }
    double d;
    while (scanf("%lf", &d), d > 0.01) {
        printf("%6.2lf%17llu\n", d, ways[int(round(d * 100 / 5))]);
    }
}
