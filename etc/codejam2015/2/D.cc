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
using vs = vector<string>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const int MAX = 101;
const ll MOD = 1000000007;
ll DP[MAX][4][10];
int R, C;

ll gcd(ll a, ll b) {
  while (b) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

bool check(vvi& m, int r, int c) {
  if (r < 0 || r >= R) return true;
  c = (c + C) % C;
  const int dx[] = {-1, 1, 0, 0};
  const int dy[] = {0, 0, 1, -1};
  char v = m[r][c];
  if (v == 0) return true;
  int count = 0;
  for (int i = 0; i < 4; i++) {
    int x = r + dx[i];
    int y = (c + dy[i] + C) % C;
    if (x < 0 || x >= R) continue;
    if (m[x][y] == 0) {
      count = v;
      return true;
    }
    if (m[x][y] == v) {
      count++;
    }
  }
  return (count == v);
}

ll dp(int rows, int tabu, int mult) {
  if (rows == 0) {
    return 1;
  }
  auto &r = DP[rows][tabu][mult];
  if (r == 0) {
    if (tabu != 2) {
      r = (r + dp(rows - 1, 2, mult)) % MOD; // 222222
      if (C % 3 == 0 && rows > 1) {
        // 221
        // 221
        r = (r + gcd(mult, 3) * dp(rows - 2, 2, lcm(mult, 3))) % MOD;
      }

      if (C % 4 == 0 && rows > 2) {
        r = (r + gcd(mult, 4) * dp(rows - 3, 2, lcm(mult, 4))) % MOD;
        // 2122
        // 2121
        // 2221
      }
      if (C % 6 == 0 && rows > 1) {
        /*112222
          222112*/
        r = (r + gcd(mult, 6) * dp(rows - 2, 2, lcm(mult, 6))) % MOD;
      }
    }
    if (tabu != 3 && rows > 1) {
      r = (r + dp(rows - 2, 3, mult)) % MOD;
    }
  }
  return r;
}

vector<vvi> solutions;

void backtrack(vvi& m, int r, int c) {
  if (r == R) {
    bool found = false;
    for (auto a : solutions) {
      for (int sh = 0; sh < C && !found; sh++) {
        found = true;
        for (int i = 0; i < R && found; i++) {
          for (int j = 0; j < C && found; j++) {
            found = a[i][j] == m[i][(j + sh) % C];
          }
        }
      }
      if (found) break;
    }
    if (!found) {
      vvi s(m.size());
      for (int i = 0; i < R; i++) s[i] = m[i];
      solutions.emplace_back(s);
    }
    return;
  }
  int x = r, y = c + 1;
  if (y == C) { y = 0; x++; }
  const int dx[] = {0, -1, 1, 0, 0};
  const int dy[] = {0, 0, 0, 1, -1};
  for (int i = 1; i < 4; i++) {
    m[r][c] = i;
    bool ok = true;
    for (int j = 0; j < 5; j++) {
      ok = ok && check(m, r + dx[j], c + dy[j]);
    }
    if (ok) backtrack(m, x, y);
  }
  m[r][c] = 0;
}

int main() {/*
  for (R = 1; R < 13; R++) {
    vvi m(R);
    for (C = 1; C < 13; C++) {
      solutions.clear();
      for (int i = 0; i < R; i++) {
        m[i].clear(); m[i].resize(C, 0);
      }

      fill(&DP[0][0][0], &DP[MAX][0][0], 0);
      ll answer = dp(R, 0, 1);
      backtrack(m, 0, 0);
      if (answer == solutions.size()) continue;
      cout << R << " x " << C;
      cout << " (" << answer << ")";
      cout << " <<<<<<<< " << solutions.size();
      cout << endl;
      sort(solutions.begin(), solutions.end(), [&] (const vvi& a, const vvi& b) {
        for (int i = 0; i < R; i++) {
          for (int j = 0; j < C; j++) {
            if (a[i][j] == b[i][j]) continue;
            return a[i][j] < b[i][j];
          }
        }
        return false;
      });
      for (auto a : solutions) {
        for (int i = 0; i < R; i++) {
          for (int j = 0; j < C; j++) {
            cout << a[i][j];
          }
          cout << endl;
        }
        cout << endl;
      }
      return 0;
    }
  }
  */
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cin >> R >> C;
    fill(&DP[0][0][0], &DP[MAX][0][0], 0);
    ll answer = dp(R, 0, 1);
    cout << "Case #" << tc << ": " << answer << endl;
  }
}
