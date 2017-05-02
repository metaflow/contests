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

// TODO add to integers snippet
// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
l extended_euclid(l a, l b, l& x, l& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  l d = extended_euclid(b, a % b, x, y);
  l t = y;
  y = x - (a / b) * y;
  x = t;
  return d;
}

l divup(l a, l b) { // ceil div
  return (a + b - 1) / b;
}

// return b: a * b = 1 (mod n)
l inverse_mod(l a, l n) {
  l x, y;
  l d = extended_euclid(a, n, x, y);
  if (d != 1) return 0;
  return (x + (abs(x) / n + 1) * n) % n;
}

// (a * b) % mod, safe for l near max
l mult_mod(l a, l b, l mod) {
  l x = 0;
  while (b) {
    if (b % 2) x = (x + a) % mod;
    a = (a * 2) % mod;
    b /= 2;
  }
  return x;
}


l nCr(l n, l k, l mod) {
  l a = 1;
  for (l i = n; i > n - k; i--) a = mult_mod(a, i, mod);
  l b = 1;
  F(i, 1, k + 1) b = mult_mod(b, i, mod);
  b = inverse_mod(b, mod);
  return mult_mod(a, b, mod);
}

const l MOD = e9 + 7;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k;
  while (cin >> n >> k) {
    vl v(n); F(i, 0, n) cin >> v[i];
    vl g = v;
    l answer = 0;
    for (l d = 63; d >= 0; d--) {
      vl next;
      for (auto x : g)
        if (x & (1LL << d)) {
          next.emplace_back(x);
        }
      if ((l)next.size() >= k) {
        answer += (1LL << d);
        swap(g, next);
      }
    }
    cout << answer << lf << nCr(g.size(), k, MOD) << lf;
  }
}
