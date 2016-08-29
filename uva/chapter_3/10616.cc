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

using ll = long long;

ll memo[20][200][11][21];
int values[200];

ll count(int r, int k, int m, int d) {
    if (m == 0) {
        if (r == 0) return 1;
        return 0;
    }
    if (k + 1 < m) return 0;
    ll &t = memo[r][k][m][d];
    if (t == -1) {
        t = count(((r + values[k]) % d + d) % d, k - 1, m - 1, d);
        t += count(r, k - 1, m, d);
    }
    return t;
}

int main() {
    int n, q;
    int tc = 0;
    while (cin >> n >> q, n) {
        tc++;
        printf("SET %d:\n", tc);
        for (int i = 0; i < n; i++) cin >> values[i];
        fill(&memo[0][0][0][0], &memo[20][0][0][0], -1);
        for (int i = 0; i < q; i++) {
            int m, d;
            cin >> d >> m;
            printf("QUERY %d: %lld\n", i + 1, count(0, n - 1, m, d));
        }
    }
}
