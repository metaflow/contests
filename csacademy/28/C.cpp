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

void transform(vl& v) {
  l n = v.size();
  vl next;
  F(j, 0, n) if (j % 2 == 0) next.emplace_back(v[j]);
  F(j, 0, n) if (j % 2 == 1) next.emplace_back(v[j]);
  v.clear();
  F(j, 0, (n + 1) / 2) {
    v.emplace_back(next[j]);
    if (n - 1 - j != j) v.emplace_back(next[n - 1 - j]);
  }
  reverse(all(v));

}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k;
  while (cin >> n >> k) {
    vl v(n);
    F(i, 0, n) v[i] = i;
    l cycle = 0;
    F(i, 0, 10) {
      bool f = true;
      transform(v);
      F(j, 0, n) f = f and v[i] == i;
      if (f) {
        cycle = i + 1;
        break;
      }
    }
    F(i, 0, k % cycle) {
      transform(v);
    }
    F(i, 0, n) {
      if (i) cout << ' ';
      cout << (v[i] + 1);
    }
    cout << lf;
  }
}
