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

const int MAX = 1001;

int main() {
    ll q[MAX][MAX];
    int n, m;
    ll values[MAX];
    while (scanf("%d%d", &n, &m), n) {
        fill(&q[0][0], &q[MAX][0], 0);
        fill(&q[0][0], &q[1][0], 1);
        for (int i = 1; i <= n; i++) scanf("%lld", values + i);
        ll best = 0;
        for (int k = 1; k <= n; k++) {
            for (int x = 1; x <= n; x++) {
                q[k][x] = (values[x] * q[k - 1][x - 1] + q[k][x - 1]) % m;
            }
            best = max(best, q[k][n]);
        }
        printf("%lld\n", best);
    }
}
