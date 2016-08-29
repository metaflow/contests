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
using llu = long long;

int n;
const int MAX_N = 20;

llu a[MAX_N][MAX_N];

llu f(int i, int j) {
    llu &r = a[i][j];
    if (r == -1) {
        if (i < j) {
            for (int k = i; k < j; k++) {
                r = max(r, f(i, k) + f(k + 1, j));
            }
            return r;
        }
        llu q = 0;
        if (i < n) {
            for (int k = i + 1; k <= n; k++) {
                q = max(q, f(k, 1) + f(k, j));
            }
        }
        llu t = 0;
        if (j > 0) {
            for (int k = 1; k < j; k++) {
                t = max(t, f(i, k) + f(n, k));
            }
        }
        r = q + t;
    }
    return r;
}

int main() {
    int v;
    while (cin >> n >> v) {
        fill(&a[0][0], &a[MAX_N][0], -1);
        a[n][1] = v;
        cout << f(1, n) << endl;
    }
}
