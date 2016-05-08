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

bool out(vvi& m, int r, int c, int d) {
  if (d == -1) return false;
  const int dx[] = {-1, 0, 1, 0};
  const int dy[] = {0, 1, 0, -1};
  int x = r, y = c;
  while (true) {
    x += dx[d];
    y += dy[d];
    if (x < 0 || y < 0 || x >= m.size() || y >= m[0].size()) return true;
    if (m[x][y] != -1) return false;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int rows, cols;
    cin >> rows >> cols;
    vvi m(rows);
    for (int i = 0; i < rows; i++) {
      m[i].resize(cols);
      string s; cin >> s;
      for (int j = 0; j < cols; j++) {
        int v = -1;
        switch (s[j]) {
          case '^': v = 0; break;
          case '>': v = 1; break;
          case 'v': v = 2; break;
          case '<': v = 3; break;
        }
        m[i][j] = v;
      }
    }
    ll answer = 0;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (out(m, r, c, m[r][c])) {
          bool ok = false;
          for (int i = 0; i < 4; i++) {
            if (i == m[r][c]) continue;
            if (!out(m, r, c, i)) {
              ok = true;
            }
          }
          if (ok) {
            answer++;
          } else {
            answer = -INF;
          }
        }
      }
    }
    cout << "Case #" << tc << ": ";
    if (answer < 0) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << answer << endl;
    }
  }
}
