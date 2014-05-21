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

ll memo[101][2];

int k, d;

ll count(int n, int used_d) {
    if (n < 0) return 0;
    if (n == 0) return used_d;
    ll &v = memo[n][used_d];
    if (v == -1) {
        v = 0;
        for (int i = 1; i <= k; i++) {
            v += count(n - i, (used_d || i >= d) ? 1 : 0);
            v %= 1000000007;
        }
    }
    return v;
}

int main() {
    int n;
    cin >> n >> k >> d;
    fill(&memo[0][0], &memo[101][0], -1);
    cout << count(n, 0) << endl;
}
