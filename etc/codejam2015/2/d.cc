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

bool check(vvi& m) {
  const int dx[] = {-1, 1, 0, 0};
  const int dy[] = {0, 0, 1, -1};
  int max_y = m[0].size() - 1;
  int max_x = m.size() - 1;
  for (int r = 0; r <= max_x; r++) {
    for (int c = 0; c <= max_y; c++) {
      int v = m[r][c];
      int count = 0;
      for (int i = 0; i < 4; i++) {
        int x = r + dx[i];
        int y = c + dy[i];
        if (x < 0 || x > max_x) continue;
        if (y > max_y) y = 0;
        if (y < 0) y = max_y;
        if (m[x][y] == v) {
          count++;
        }
      }
      if (count != v) {
        return false;
      }
    }
  }
  return true;
}

const int MAX = 101;
const ll MOD = 1000000007;
ll DP[MAX][4];
int R, C;

ll dp(int rows, int tabu) {
  if (rows == 0) {
    return 1;
  }
  ll &r = DP[rows][tabu];
  if (r == 0) {
    if (tabu != 2) {
      r = (r + dp(rows - 1, 2)) % MOD; // row of 2
      if (C % 3 == 0 && rows > 1) {
        r = (r + dp(rows - 2, 2)) % MOD;
        // row of
        // 221
        // 221
        // 221
      }
      if (C % 4 == 0 && rows > 2) {
        r = (r + dp(rows - 3, 2)) % MOD;
        // row of
        // 2122
        // 2121
        // 2221
      }
    }
    if (tabu != 3 && rows > 1) {
      r = (r + dp(rows - 2, 3)) % MOD;
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cin >> R >> C;
    fill(&DP[0][0], &DP[MAX][0], 0);
    ll answer = dp(R, 0);
    cout << "Case #" << tc << ": " << answer << endl;
  }
}
