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
  l n;
  while (cin >> n) {
    vll W, D, L;
    F(i, 0, n) {
      char c; l a, b;
      cin >> c >> a >> b;
      switch(c) {
      case 'W': W.emplace_back(a + b, b); break;
      case 'D': D.emplace_back(a + b, b); break;
      case 'L': L.emplace_back(a + b, b); break;
      }
    }
    l m = 0;
    l t = 0;
    for (auto i : W) t += i.first;
    m = max(m, t);
    t = 0;
    for (auto i : D) t += i.first;
    m = max(m, t);
    t = 0;
    for (auto i : L) t += i.first;
    m = max(m, t);
    vl dw(m + 1, 0);
    auto dd = dw, dl = dw;
    for (auto p : W) for(l i = m; i >= 0; i--) {
      l x = i + p.first;
      if (x > m) continue;
      dw[x] = max(dw[x], dw[i] + p.second);
    }
    for (auto p : D) for(l i = m; i >= 0; i--) {
        l x = i + p.first;
        if (x > m) continue;
        dd[x] = max(dd[x], dd[i] + p.second);
      }
    for (auto p : L) for(l i = m; i >= 0; i--) {
        l x = i + p.first;
        if (x > m) continue;
        dl[x] = max(dl[x], dl[i] + p.second);
      }
    l answer = 0;
    F(i, 0, m + 1) {
      answer = max(answer, dw[i] + dd[i] + dl[i] - i);
    }
    cout << answer << lf;
  }
}
