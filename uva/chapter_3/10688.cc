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

const int MAX = 501;

int memo[MAX][MAX];

int w(int from, int to) {
    if (from >= to) return 0;
    int &r = memo[from][to];
    if (r == 0) {
        r = numeric_limits<int>::max();
        for (int i = from; i <= to; i++) {
            r = min(r, i * (to - from + 1) + w(from, i - 1) + w(i + 1, to));
        }
    }
    return r;
}

int main() {
    int tcc;
    fill(&memo[0][0], &memo[MAX][0], 0);
    scanf("%d", &tcc);
    for (int tc = 1; tc <= tcc; tc++) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("Case %d: %d\n", tc, w(k + 1, k + n));
    }
}
