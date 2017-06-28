#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "E"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-15; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct point {
  l x, y;
  point() {}
  point(l _x, l _y) : x(_x), y(_y) {}
  // scalar multiplication
  l operator * (const point & o) {
    return x * o.x + y * o.y;
  }
  point operator * (const l m) {
    return point(x * m, y * m);
  }
  // vector multiplication
  l operator ^ (const point & o) {
    return x * o.y - y * o.x;
  }
  point operator - (const point& o) {
    return point(x - o.x, y - o.y);
  }
  point operator + (const point& o) {
    return point(x + o.x, y + o.y);
  }
  // squared distance
  l operator >> (const point& o) {
    point d = (*this - o);
    return d * d;
  }
  double distance(const point& o) {
    return sqrt(*this >> o);
  }
  bool operator < (const point& o) const {
    if (o.x != x) return x < o.x;
    return y < o.y;
  }
};

// 0 - no intersection, 1 - point o1, 2 - segment [o1, o2]
l segment_intersection(point a, point b, point c, point d, point& o1, point &o2) {
  point x = c - a, y = d - a, z = b - a;
  double t = (x ^ z) + (z ^ y);
  if (abs(t) < EPS) {
    if (abs(x ^ y) < EPS) {
      vector<point> v = {a, b, c, d};
      sort(all(v));
      o1 = v[1];
      o2 = v[2];
      return 2;
    } else {
      return 0;
    }
  }
  t = (x ^ y) / t;
  if (t < 0 or t > 1) return 0;
  o1 = o2 = a + z * t;
  return 1;
}
ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}


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

const l MOD = e9 + 7;

void solve(istream& cin, ostream& cout) {
  l n, k;
  while (cin >> n >> k) {
    vector<point> pp(n);
    F(i, 0, n) cin >> pp[i].x >> pp[i].y;
    point o; cin >> o.x >> o.y;
    l j = 0;
    l answer = nCr(n, k, MOD);
    vl c(n - k + 2); // c[i] = C((i + k - 1), k - 1)
    c[0] = 1;
    F(i, 1, n - k + 2) {
      c[i] = mult_mod(mult_mod(c[i - 1], (i + k - 1), MOD),
                      inverse_mod(i, MOD),
                      MOD);
    }
    F(i, 0, n) {
      while (((pp[i] - o) ^ (pp[cong(j + 1, n)] - o)) >= 0) j++;
      // debug(i, j);
      if (j - i < k - 1) continue;
      answer = cong(answer - c[j - i - k + 1], MOD);
    }
    cout << answer << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
