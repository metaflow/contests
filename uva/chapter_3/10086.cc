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

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int INF = numeric_limits<int>::max();
const int MAX_N = 31;
const int MAX_M = 21;
const int MAX_T = 301;

int value_t1[MAX_N][MAX_M], value_t2[MAX_N][MAX_M];
int memo_sum[MAX_N][MAX_T], memo_t1[MAX_N][MAX_T];
int m[MAX_N];

int best_t1(int k, int t1, int t2) {
    int &p = memo_t1[k][t1];
    if (p == -1) {
        int best_sum = INF;
        for (int i = max(0, m[k] - t2); i <= t1 && i <= m[k]; i++) {
            int v = value_t1[k][i] + value_t2[k][m[k] - i];
            if (k != 1) {
                best_t1(k - 1, t1 - i, t2 - (m[k] - i));
                v += memo_sum[k - 1][t1 - i];
            }
            if (v >= best_sum) continue;
            best_sum = v;
            p = i;
        }
        memo_sum[k][t1] = best_sum;
    }
    return p;
}

int main() {
    int t1, t2, n;
    while (cin >> t1 >> t2, t1 + t2) {
        fill(&memo_t1[0][0], &memo_t1[MAX_N][0], -1);
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> m[i];
            value_t1[i][0] = 0;
            for (int j = 1; j <= m[i]; j++) cin >> value_t1[i][j];
            value_t2[i][0] = 0;
            for (int j = 1; j <= m[i]; j++) cin >> value_t2[i][j];
        }
        int a = t1, b = t2;
        int answer[MAX_N];
        for (int k = n; k > 0; k--) {
            answer[k] = best_t1(k, a, b);
            a -= answer[k];
            b -= (m[k] - answer[k]);
        }
        cout << memo_sum[n][t1] << endl;
        for (int k = 1; k <= n; k++) {
            if (k != 1) cout << ' ';
            cout << answer[k];
        }
        cout << endl << endl;
    }
}
