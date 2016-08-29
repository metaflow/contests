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
using iii = tuple<int, int, int>;
using ll = long long;
using llu = unsigned long long;
const int MAX = 1000;
const int INF = numeric_limits<int>::max();

int g[MAX][MAX], w[MAX][MAX];
int n, m;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void dijkstra(int x, int y) {
  fill(&w[0][0], &w[MAX][0], INF);
  w[x][y] = g[x][y];
  priority_queue<iii, vector<iii>, greater<iii>> pq;
  pq.push(iii(w[x][y], x, y));
  while (!pq.empty()) {
    int a = get<1>(pq.top());
    int b = get<2>(pq.top());
    int d = get<0>(pq.top());
    pq.pop();
    if (d > w[a][b]) continue;
    for (int i = 0; i < 4; ++i) {
      int e = a + dx[i];
      int f = b + dy[i];
      if (e >= n || f >= m || e < 0 || f < 0) continue;
      if (d + g[e][f] < w[e][f]) {
        w[e][f] = d + g[e][f];
        pq.push(iii(w[e][f], e, f));
      }
    }
  }
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> g[i][j];
      }
    }
    dijkstra(0, 0);
    printf("%d\n", w[n - 1][m - 1]);
  }
}
