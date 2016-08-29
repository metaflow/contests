#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 75;
ll memo[MAX][MAX][6][3];
int values[MAX][MAX];
const int RIGHT = 1;
const int LEFT = 2;

int n;

ll backtrack(int x, int y, int k, int from) {
  if (x < 0 || y < 0 || y >= n) return -INF;
  auto v = values[x][y];
  if (v < 0) k--;
  if (k < 0) return -INF;
  if (x == 0 && y == 0) return v;

  ll &r = memo[x][y][k][from];
  if (r == INF) {
    r = -INF;
    ll t;

    if (from != RIGHT) {
      t = backtrack(x, y + 1, k, LEFT);
      if (t != -INF) r = max(r, t + v);
    }
    if (from != LEFT) {
      t = backtrack(x, y - 1, k, RIGHT);
      if (t != -INF) r = max(r, t + v);
    }
    t = backtrack(x - 1, y, k, 0);
    if (t != -INF) r = max(r, t + v);
  }
  return r;
}

int main() {
  int k;
  int tc = 0;
  while (cin >> n >> k, n) {
    tc++;
    fill(&memo[0][0][0][0], &memo[MAX][0][0][0], INF);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> values[i][j];
      }
    }
    ll t = backtrack(n - 1, n - 1, k, 0);
    if (t == -INF) {
      printf("Case %d: impossible\n", tc);
    } else {
      printf("Case %d: %lld\n", tc, t);
    }
  }
}
