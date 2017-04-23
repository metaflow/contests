// #define ONLINE_JUDGE
#include <bits/stdc++.h>
#if !defined(ONLINE_JUDGE)
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

#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    cout << "Case #" << tc << ":";
    l n, q; cin >> n >> q;
    vector<pair<l, double>> hourses(n); // (distance, speed)
    F(i, 0, n) cin >> hourses[i].first >> hourses[i].second;
    vvl d(n, vl(n));
    F(i, 0, n) F(j, 0, n) {
      cin >> d[i][j];
    }
    F(k, 0, n) F(i, 0, n) F(j, 0, n) {
      if (d[i][k] > -1 and d[k][j] > -1) {
        l t = d[i][k] + d[k][j];
        if (t < d[i][j] or d[i][j] == -1) d[i][j] = t;
      }
    }
    while (q--) {
      l a, b; cin >> a >> b; a--; b--;
      vd time(n, -1);
      vector<bool> in_queue(n);
      queue<l> u;
      time[a] = 0;
      u.emplace(a);
      in_queue[a] = true;
      while (not u.empty()) {
        l i = u.front(); u.pop();
        in_queue[i] = false;
        F(j, 0, n) if (d[i][j] > -1 and d[i][j] <= hourses[i].first) {
          double t = d[i][j] / hourses[i].second + time[i];
          if (time[j] < 0 or time[j] > t) {
            time[j] = t;
            if (not in_queue[j]) {
              u.emplace(j);
              in_queue[j] = true;
            }
          }
        }
      }
      cout << ' ' << fixed << setprecision(9) << time[b];
    }
    cout << lf;
  }
}
