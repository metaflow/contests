#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const int MAX = 16;

ll D[MAX][MAX];
struct point { int x, y; };
const int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = { 1, -1, 2, -2, 2, -2, 1, -1};
ll dpm[MAX][1 << MAX];

ll dp(ll mask, int p) {
  ll &r = dpm[p][mask];
  if (r < 0) {
    if (mask == 0) {
      r = D[p][0];
      return r;
    }
    r = INF;
    for (int i = 1; i < MAX; i++) {
      if (mask & (1 << i)) {
        r = min(r, D[p][i] + dp(mask ^ (1 << i), i));
      }
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  const int MAXS = 1100;
  int space[MAXS][MAXS];
  fill(&space[0][0], &space[MAXS][0], INF);
  queue<pair<int, int>> q;
  space[10][10] = 0;
  q.emplace(10, 10);
  while (!q.empty()) {
    int x0, y0; tie(x0, y0) = q.front(); q.pop();
    for (auto jj = 0; jj < 8; jj++) {
      int x = x0 + dx[jj], y = y0 + dy[jj];
      if (x < 0 || y < 0 || x >= MAXS || y >= MAXS) continue;
      if (space[x][y] != INF) continue;
      space[x][y] = space[x0][y0] + 1;
      q.emplace(x, y);
    }
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, s; cin >> s >> n;
    vector<point> K(n);
    fill(&D[0][0], &D[MAX][0], INF);
    for (ll ii = 0; ii < n; ii++) cin >> K[ii].x >> K[ii].y;
    for (ll ii = 0; ii < n; ii++) {
      D[ii][ii] = 0;
      vvi my(s + 1);
      for (ll jj = 0; jj < s + 1; jj++) my[jj].resize(s + 1, INF);
      queue<pair<int, int>> q;
      my[K[ii].x][K[ii].y] = 0;
      q.emplace(K[ii].x, K[ii].y);
      while (!q.empty()) {
        int x0, y0; tie(x0, y0) = q.front(); q.pop();
        int d = my[x0][y0];
        for (ll jj = 0; jj < 8; jj++) {
          int x = x0 + dx[jj], y = y0 + dy[jj];
          if (x < 1 || y < 1 || x > s || y > s) continue;
          if (my[x][y] != INF) continue;
          my[x][y] = d + 1;
          if (d < 3) q.emplace(x, y);
        }
      }
      for (ll jj = ii + 1; jj < n; jj++) {
        int t = my[K[jj].x][K[jj].y];
        if (t == INF) {
          int x1 = K[ii].x, y1 = K[ii].y, x2 = K[jj].x, y2 = K[jj].y;
          if (x1 > x2) swap(x1, x2);
          if (y1 > y2) swap(y1, y2);
          t = space[10 + x2 - x1][10 + y2 - y1];
        }
        D[ii][jj] = D[jj][ii] = t;
      }
    }
    fill(&dpm[0][0], &dpm[MAX][0], -1);
    ll answer = dp((1 << n) - 2, 0);
    cout << "Case " << tc << ": " << answer << endl;
  }
}

