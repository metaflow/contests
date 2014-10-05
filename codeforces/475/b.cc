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
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 400;
bool g[MAX][MAX];

int main() {
  int n, m, i, j, k;
  while (cin >> n >> m) {
    fill(&g[0][0], &g[MAX][0], false);
    string s;
    cin >> s;
    for (i = 0; i < n; i++) {
      char c = s[i];
      for (j = 0; j < m - 1; j++) {
        int f = j + i * m;
        int t = j + 1 + i * m;
        if (c == '>') {
          g[f][t] = true;
        } else {
          g[t][f] = true;
        }
      }
    }
    cin >> s;
    for (i = 0; i < m; i++) {
      char c = s[i];
      for (j = 0; j < n - 1; j++) {
        int f = j * m + i;
        int t = (j + 1) * m + i;
        if (c == 'v') {
          g[f][t] = true;
        } else {
          g[t][f] = true;
        }
      }
    }

    int total = m * n;
    for (i = 0; i < total; i++) g[i][i] = true;

    for (k = 0; k < total; k++)
    for (i = 0; i < total; i++)
    for (j = 0; j < total; j++)
      g[i][j] = g[i][j] || (g[i][k] && g[k][j]);

    bool ok = true;

    for (i = 0; (i < total) && ok; i++)
    for (j = 0; (j < total) && ok; j++) ok = ok && g[i][j];

    if (ok) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}

