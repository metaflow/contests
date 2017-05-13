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
  l n, m;
  while (cin >> n >> m) {
    vvl edges(n);
    vl w(n, INF);
    unordered_map<l, l> c;
    F(i, 0, m) {
      l u, v; cin >> u >> v; u--; v--;
      edges[u].emplace_back(v);
      edges[v].emplace_back(u);
    }
    c[0] = 1;
    w[0] = 0;
    for (auto a : edges[0]) {
      w[a] = 1;
      c[1]++;
    }
    for (auto a : edges[0]) {
      l j = 1;
      for (auto b : edges[a]) {
        if (w[b] == 1) j++;
      }
      if (j != c[1]) {
        w[a] = -1;
        c[1]--;
        c[-1]++;
        for (auto b : edges[a]) {
          if (w[b] == 1) {
            w[b] = -1;
            c[1]--;
            c[-1]++;
          }
        }
        break;
      }
    }
    queue<l> q;
    for (auto a : edges[0]) q.emplace(a);
    bool ok = true;
    while (ok and not q.empty()) {
      auto a = q.front(); q.pop();
      l j = 1;
      for (auto b : edges[a]) {
        if (w[b] == INF) {
          if (w[a] > 0) {
            w[b] = w[a] + 1;
          } else {
            w[b] = w[a] - 1;
          }
          c[w[b]]++;
          q.emplace(b);
          continue;
        }
        if (w[a] == w[b]) j++;
        if (abs(w[a] - w[b]) > 1) ok = false;
      }
      if (j != c[w[a]]) ok = false;
    }
    l r = 0;
    for (auto a : w) r = min(a, r);
    if (ok) {
      cout << "YES" << lf;
      F(i, 0, n) {
        if (i) cout << ' ';
        cout << (w[i] - r + 1);
      }
      cout << lf;
    } else {
      cout<< "NO" << lf;
    }
  }
}
