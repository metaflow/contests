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
const int MAX = 1010;

int g[MAX][MAX];
int total = 0;

int area(int x1, int y1, int x2, int y2) {
  --x1;
  --y1;
  return g[x2][y2] - g[x1][y2] - g[x2][y1] + g[x1][y1];
}

bool filled(int x1, int y1, int x2, int y2) {
  return area(x1, y1, x2, y2) == (x2 - x1 + 1) * (y2 - y1 + 1);
}

ii rectangle_at(int x, int y) {
  ii r;
  r.first = 0;
  r.second = 0;
  while (filled(x, y, x + r.first + 1, y + r.second)) r.first++;
  while (filled(x, y, x + r.first, y + r.second + 1)) r.second++;
  r.first++;
  r.second++;
  return r;
}

vector<ii> get_sizes(ii p) {
  vector<ii> r;
  for (int i = 1; i <= p.first; i++) r.emplace_back(ii(i, p.second));
  for (int i = 1; i <= p.second - 1; i++) r.emplace_back(ii(p.first, i));
  return r;
}

int test(int x, int y, vector<ii> v, int a) {
  auto p = rectangle_at(x, y);
  vector<ii> r;

  for (auto c : v) {
    if (c.first == p.first && c.second <= p.second) r.emplace_back(c);
    if (c.first <= p.first && c.second == p.second) r.emplace_back(c);
  }
  if (r.empty()) return INF;
  int t = area(x, y, x + p.first - 1, y + p.second - 1);
  int s = area(1, 1, x + p.first - 1, y + p.second - 1);
  if (a + t != s) return INF;
  int w = area(x, y, x + p.first,     y + p.second - 1) - t;
  int h = area(x, y, x + p.first - 1, y + p.second    ) - t;
  int best = INF;

  if (h == 0 && w == 0) {
    if (s != total) return INF;
    for (auto x : r) best = min(best, x.first * x.second);
    return best;
  }

  if (h != 0) {
    best = min(best, test(x + p.first - h, y, r,
          a + (p.first - h) * p.second));
  }

  if (w != 0) {
    best = min(best, test(x, y + p.second - w, r,
          a + p.first * (p.second - w)));
  }

  return best;
}

int main() {
  int n, m, i, j;
  while (cin >> n >> m) {
    fill(&g[0][0], &g[MAX][0], 0);
    string s;
    for (i = 1; i <= n; i++) {
      cin >> s;
      for (j = 1; j <= m; j++) {
        g[i][j] = (s[j - 1] == 'X' ? 1 : 0);
      }
    }
    for (int i = 1; i <= n + 1; i++) {
      for (int j = 1; j <= m + 1; j++) {
        g[i][j] = g[i][j] + g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
      }
    }
    int x = -1, y = -1;
    for (int i = 1; i <= n && x == -1; i++)
    for (int j = 1; j <= m && x == -1; j++) {
      if (g[i][j] == 0) continue;
      x = i;
      y = j;
    }
    total = g[n][m];
    auto p = rectangle_at(x, y);
    int t = test(x, y, get_sizes(p), 0);
    if (t == INF) {
      cout << -1 << endl;
    } else {
      cout << t << endl;
    }
  }
}

