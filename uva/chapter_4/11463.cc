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
const int INF = numeric_limits<int>::max() / 2;
const int MAX = 100;

int w[MAX][MAX];

int main() {
  int tcc, i, j, k, a, b, n, r, t;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    fill(&w[0][0], &w[MAX][0], INF);
    cin >> n >> r;
    for (i = 0; i < n; i++) w[i][i] = 0;
    for (i = 0; i < r; i++) {
      cin >> a >> b;
      w[a][b] = w[b][a] = 1;
    }

    for (k = 0; k < n; k++)
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) w[i][j] = min(w[i][j], w[i][k] + w[k][j]);

    cin >> a >> b;
    t = 0;
    for (i = 0; i < n; i++) t = max(t, w[a][i] + w[i][b]);
    printf("Case %d: %d\n", tc, t);
  }
}
