#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 100;

int d[MAX][MAX];

int main() {
  string a, b;
  bool first = true;
  while (getline(cin, a)) {
    getline(cin, b);
    if (!first) printf("\n"); first = false;
    fill(&d[0][0], &d[MAX][0], 0);
    for (size_t i = 1; i <= a.size(); i++) d[i][0] = i;
    for (size_t i = 1; i <= b.size(); i++) d[0][i] = i;
    for (size_t i = 1; i <= a.size(); i++) {
      for (size_t j = 1; j <= b.size(); j++) {
        if (a[i - 1] == b[j - 1]) {
          d[i][j] = d[i-1][j-1];
        } else {
          d[i][j] = min(d[i-1][j-1], min(d[i-1][j], d[i][j - 1])) + 1;
        }
      }
    }
    printf("%d\n", d[a.size()][b.size()]);
    int x = a.size();
    int y = b.size();
    stack<ii> path;
    path.emplace(x, y);
    while (x != 0 || y != 0) {
      ii p;
      int best = INF;
      for (int i = max(0, x - 1); i <= x; i++) {
        for (int j = max(0, y - 1); j <= y; j++) {
          if (d[i][j] < best) {
            best = d[i][j];
            p.first = i;
            p.second = j;
          }
        }
      }
      x = p.first;
      y = p.second;
      path.emplace(p);
    }
    int u = 0, step = 0;
    while (!path.empty()) {
      auto p = path.top(); path.pop();
      int _x = x, _y = y;
      x = p.first;
      y = p.second;
      if (d[_x][_y] == d[x][y]) { // same
        u++;
        continue;
      }
      step++;
      if (_x == x) {
        printf("%d Insert %d,%c\n", step, u, b[y - 1]);
        u++;
      } else if (_y == y) {
        printf("%d Delete %d\n", step, u);
      } else {
        printf("%d Replace %d,%c\n", step, u, b[y - 1]);
        u++;
      }
    }
  }
}
