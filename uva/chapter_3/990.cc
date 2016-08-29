#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
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

const int MAX_N = 31;
const int MAX_T = 1001;

int memo[MAX_N][MAX_T];
int depth[MAX_N], value[MAX_N];

int main() {
    int t, w;
    bool first = true;
    while (cin >> t >> w) {
        if (!first) cout << endl;
        first = false;
        w *= 3;
        fill(&memo[0][0], &memo[1][0], 0);
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> depth[i] >> value[i];
            int d = w * depth[i];
            for (int j = 0; j <= t; j++) {
                memo[i][j] = memo[i - 1][j];
                if (j > d) {
                    memo[i][j] = max(memo[i][j],
                        value[i] + memo[i - 1][j - d]);
                }
            }
        }
        cout << memo[n][t] << endl;
        stack<int> trace;
        int k = t;
        for (int i = n; i > 0; i--) {
            if (memo[i][k] == memo[i - 1][k]) continue;
            k -= depth[i] * w;
            trace.push(i);
        }
        cout << trace.size() << endl;
        while(!trace.empty()) {
            cout << depth[trace.top()] << " " << value[trace.top()] << endl;
            trace.pop();
        }
    }
}
