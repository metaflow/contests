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

const int MAX = 101;

int main() {
    int m, n;
    int a[MAX][MAX];
    fill(&a[0][0], &a[MAX][0], 0);
    while (cin >> m >> n, m) {
        for (int r = 1; r <= m; r++)
        for (int c = 1; c <= n; c++) {
            cin >> a[r][c];
            a[r][c] += a[r - 1][c] + a[r][c - 1] - a[r - 1][c - 1];
        }
        int best = 0;
        for (int b = 0; b <= m; b++)
        for (int l = 0; l <= n; l++)
        for (int t = m; t > b; t--)
        for (int r = n; r > l; r--) {
            int v = (t - b) * (r - l);
            if (v <= best) break;
            if (a[t][r] + a[b][l] - a[t][l] - a[b][r]) continue;
            best = v;
        }
        cout << best << endl;
    }
}
