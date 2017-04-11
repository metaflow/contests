#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vvl v(n, vl(m));
    F(i, 0, n) F(j, 0, m) cin >> v[i][j];
    vvl rows(n, vl(m + 1)), cols(n + 1, vl(m));
    F(i, 0, n) F(j, 0, m) {
      rows[i][j+1] = rows[i][j] + v[i][j];
      cols[i+1][j] = cols[i][j] + v[i][j];
    }
    auto good = [&](l x, l y, l k) {
      return x >= 0 and y >= 0 and x + k <= n and y + k <= m;
    };
    l best = numeric_limits<l>::min();
    F(i, 0, n) F(j, 0, m) {
      // 3 + 4z
      l sum = 0;
      l k = 3;
      l x = i, y = j;
      if (good(x, y, k)) {
        sum = rows[x][y + k] - rows[x][y] +
          rows[x + 2][y + k] - rows[x + 2][y] +
          v[x+1][y + 2];
        best = max(best, sum);
        while (1) {
          x -= 2; y -= 2; k += 4;
          if (not good(x, y, k)) break;
          sum += rows[x][y + k] - rows[x][y]
            + cols[x + k - 1][y + k - 1] - cols[x + 1][y + k - 1]
            + rows[x + k - 1][y + k] - rows[x + k - 1][y]
            + cols[x + k - 1][y] - cols[x + 2][y]
            + v[x + 2][y+1];
          best = max(sum, best);
        }
      }
      // 1 + 4z
      x = i, y = j;
      k = 1;
      sum = v[x][y]; // not considered as best
      while (1) {
        x -= 2; y -= 2; k += 4;
        if (not good(x, y, k)) break;
        sum += rows[x][y + k] - rows[x][y]
          + cols[x + k - 1][y + k - 1] - cols[x + 1][y + k - 1]
          + rows[x + k - 1][y + k] - rows[x + k - 1][y]
          + cols[x + k - 1][y] - cols[x + 2][y]
          + v[x + 2][y+1];
        best = max(sum, best);
      }
    }
    cout << best << '\n';
  }
}
