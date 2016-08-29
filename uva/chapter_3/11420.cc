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
const int MAX = 65;

int main() {
    // [x][y][0] - top unlocked, [x][y][1] - top locked
    llu ways[MAX + 1][MAX + 2][2];
    ways[1][0][1] = 0;
    ways[1][0][0] = 1;
    ways[1][1][0] = 0;
    ways[1][1][1] = 1;
    llu m = 0;
    for (int n = 2; n <= MAX; ++n)
    for (int s = 0; s <= MAX + 1; ++s)
    for (int e = 0; e <= 1; ++e) {
        llu &r = ways[n][s][e];
        if (s > n) {
            r = 0;
            continue;
        }
        if (s == n) {
            r = e;
            continue;
        }
        if (s == 0 && e == 1) {
            r = 0;
            continue;
        }
        if (e) {
            r = ways[n - 1][s - 1][1] + ways[n - 1][s - 1][0];
        } else {
            r = ways[n - 1][s + 1][1] + ways[n - 1][s][0];
        }
        m = max(m, r);
    }

    int n, s;
    while (scanf("%d%d", &n, &s), s >= 0) {
        printf("%llu\n", ways[n][s][0] + ways[n][s][1]);
    }
}
