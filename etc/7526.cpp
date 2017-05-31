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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n, m, r, s;
  while (cin >> n >> m >> r >> s, n) {
    vvl v(n, vl(m + 1));
    F(i, 0, n) {
      F(j, 0, m) {
        l x; cin >> x;
        v[i][j + 1] = v[i][j] + (1 - x);
      }
    }
    l answer = 0;
    B(w, m, 0) F(a, 0, m - w + 1) {
      if (w * n <= answer) break;
      set<ll> singles, rows;
      l sum_singles = 0;
      l up = 0; // topmost row inclusive
      F(i, 0, n) {
        l x = v[i][a + w] - v[i][a];
        rows.emplace(make_pair(x, i));
        while ((not singles.empty()) and (singles.rbegin()->first > x)) {
          auto t = *(singles.rbegin());
          singles.erase(t);
          sum_singles -= t.first;
          rows.emplace(t);
        }
        while ((l)rows.size() > r) {
          ll t = *(rows.begin());
          rows.erase(t);
          singles.emplace(t);
          sum_singles += t.first;
        }
        while (sum_singles > s) {
          ll t = make_pair(v[up][a + w] - v[up][a], up);
          up++;
          if (rows.count(t)) {
            rows.erase(t);
            auto k = *(singles.rbegin());
            rows.emplace(k);
            singles.erase(k);
            sum_singles -= k.first;
          } else {
            singles.erase(t);
            sum_singles -= t.first;
          }
        }
        l t = (i - up + 1) * w;
        answer = max(answer, t);
        if ((n - up) * w <= answer) break;
      }
    }
    cout << answer << lf;
  }
}
