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

l sign(l n) {
  if (n < 0) return -1;
  if (n == 0) return 0;
  return 1;
}

// conruent modulo, works for negative
l cong(l x, l mod) {
  return (x % mod + mod) % mod;
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

// (base^power) % mod, safe for l near max
l pow_mod(l base, l power, l mod) {
  l r = 1;
  while (power) {
    if (power % 2) r = mult_mod(r, base, mod);
    base = mult_mod(base, base, mod);
    power /= 2;
  }
  return r;
}

l divup(l a, l b) { // ceil div
  return (a + b - 1) / b;
}

// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
l extended_euclid(l a, l b, l& x, l& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  l d = extended_euclid(b, a % b, x, y);
  l t = y;
  y = x - (a / b) * y;
  x = t;
  return d;
}

// return b: a * b = 1 (mod n)
l inverse_mod(l a, l n) {
  l x, y;
  l d = extended_euclid(a, n, x, y);
  if (d != 1) return 0;
  return cong(x, n);
}

// single combintions k from n
l nCr(l n, l k, l mod) {
  l a = 1;
  for (l i = n; i > n - k; i--) a = mult_mod(a, i, mod);
  l b = 1;
  F(i, 1, k + 1) b = mult_mod(b, i, mod);
  b = inverse_mod(b, mod);
  return mult_mod(a, b, mod);
}

// precompute all combinations up to (n n)
vvl combinations(l n, l mod) {
  vvl c(n + 1, vl(n + 1));
  F(i, 0, n) {
    c[i][0] = 1;
    F(j, 1, i + 1) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }
  }
  return c;
}

void f(vb& active, vl& xx, vl& yy, vl& angles) {
  l n = active.size();
  l a = n - 1;
  while (not active[a]) a--;
  l b = a, c = a, d = 0;
  while (not active[d]) d++;
  while (not (a != b and b != c and angles[b] + angles[c] == 0)) {
    a = b; b = c; c = d;
    d = (d + 1) % n;
    while (not active[d]) d = (d + 1) % n;
    if (d < c) break;
  }
  if (angles[b] + angles[c] == 0) {
    active[b] = false; active[c] = false;
    f(active, xx, yy, angles);
    l m = 0;
    F(i, 0, n) {
      xx[i] = xx[i] << 1;
      m = max(m, xx[i]);
    }
    F(i, 0, n) {
      yy[i] = yy[i] << 1;
      m = max(m, yy[i]);
    }
    l dx = sign(xx[d] - xx[a]);
    l dy = sign(yy[d] - yy[a]);
    xx[b] = xx[a] + dx; yy[b] = yy[a] + dy;
    swap(dx, dy);
    if (angles[b] == 1) {dx = -dx;} else {dy = -dy;}
    xx[c] = xx[b] + dx; yy[c] = yy[b] + dy;
    xx[d] += dx; yy[d] += dy;
    if (m > e8) {
      map<l,l> mx, my;
      for (auto i : xx) mx[i] = i;
      l t = 0;
      for (auto& kv : mx) kv.second = t++;
      for (auto& x : xx) x = mx[x];

      for (auto i : yy) my[i] = i;
      t = 0;
      for (auto& kv : my) kv.second = t++;
      for (auto& y : yy) y = my[y];
    }
  } else {
    assert(a < b);
    xx[a] = 0; yy[a] = 0;
    xx[b] = 1; yy[b] = 0;
    xx[c] = 1; yy[c] = 1;
    xx[d] = 0; yy[d] = 1;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl angles(n);
    F(i, 0, n) {
      l x; cin >> x; angles[i] = (x == 90) ? 1 : -1;
    }
    l t = accumulate(all(angles), 0);
    if (t == 4) {
      vb active(n, true);
      vl xx(n), yy(n);
      f(active, xx, yy, angles);
      F(i, 0, n) cout << xx[i] << ' ' << yy[i] << lf;
    } else {
      cout << -1 << lf;
    }
  }
}
