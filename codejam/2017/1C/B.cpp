#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

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
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l DAY = 24 * 60;
l DP[2][2][DAY][DAY];

l f(l side, l initial, l t1, l t2, l t, vvb sch) {
  if (t1 > DAY / 2 or t2 > DAY / 2) return INF;
  if (t == -1) return abs(side - initial);
  if (sch[side][t]) return INF;
  l& r = DP[side][initial][t1][t];
  if (r == -1) {
    if (side == 0) {
      t1++;
    } else {
      t2++;
    }
    r = min(f(side, initial, t1, t2, t - 1, sch),
            f(1 - side, initial, t1, t2, t - 1, sch) + 1);
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    cout << "Case #" << tc << ": ";
    l n, m; cin >> n >> m;
    vvb sch(2, vb(DAY)); // 1 if activity
    F(i, 0, n) {
      l a, b; cin >> a >> b;
      F(j, a, b) sch[0][j] = true;
    }
    F(i, 0, m) {
      l a, b; cin >> a >> b;
      F(j, a, b) sch[1][j] = true;
    }
    fill(&DP[0][0][0][0], &DP[2][0][0][0], -1);
    l answer = min(f(0, 0, 0, 0, DAY - 1, sch), f(1, 1, 0, 0, DAY - 1, sch));
    cout << answer << lf;
  }
}
