#define ONLINE_JUDGE
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

l count_(vl v, function<bool(l)> f) {
  l n = v.size();
  l t = 0;
  F(i, 0, v.size()) {
    if (f(v[i])) continue;
    if (i == n - 1) {
      t = INF;
      break;
    }
    t++;
    F(j, i + 1, min(i + 3, n)) v[j]++;
  }
  return t;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl v(n); F(i, 0, n) cin >> v[i];
    auto w = v;
    F(i, 0, min(2LL, n)) w[i]++;
    l a = count_(v, [](l x) { return x % 2 != 0; });
    a = min(a, 1 + count_(w, [](l x) { return x % 2 != 0; }));
    if (a == INF) a = - 1;
    l b = count_(v, [](l x) { return x % 2 == 0; });
    b = min(b, 1 + count_(w, [](l x) { return x % 2 == 0; }));
    if (b == INF) b = - 1;
    cout << a << lf << b << lf;
  }
}
