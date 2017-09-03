#if defined(LOCAL)
#define PROBLEM_NAME "c"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

l gcd(l a, l b) {
  while (b) { l t = b; b = a % b; a = t; }
  return a;
}

l lcm(l a, l b) { return a * b / gcd(a, b); }

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

struct Rat {
  l a, b;
  bool operator < (Rat const& rhs) const {
    if (rhs.b == 0 and b == 0) {
      return a < rhs.a;
    }
    if (b == 0) return a < 0;
    if (rhs.b == 0) return rhs.a > 0;
    return a * rhs.b < rhs.a * b;
  }

  void set(l na, l nb) {
    a = na; b = nb;
    normalize();
  }

  void set(l na) {
    set(na, 1);
  }

  void normalize() {
    l g = gcd(abs(a), abs(b));
    assert(g);
    a /= g;
    b /= g;
    if (a == 0) b = 1;
    if (b == 0) a = sign(a);
    if (b < 0 and a != 0) {
      a = -a;
      b = -b;
    }
  }
};

ostream& operator << (ostream& s, const Rat& p) {
  s << p.a << " / " << p.b;
  return s;
}

struct Line {
  Rat x0, d;

  bool operator < (Line const& rhs) const {
    if (x0 < rhs.x0) return true;
    if (rhs.x0 < x0) return false;
    return d < rhs.d;
  }
};

l const MOD = 998244353;

l set2(l n) {
  return cong(pow_mod(2, n, MOD) - n - 1, MOD);
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  vl x(n), y(n);
  F(i, 0, n) cin >> x[i] >> y[i];
  map<Line, l> m;
  F(i, 0, n) F(j, i + 1, n) {
    Line q;
    q.d.set(y[j] - y[i], x[j] - x[i]);
    if (q.d.b == 0) q.d.a = 1;
    if (y[i] == y[j]) {
      q.x0.set(y[i]);
      q.d.set(-1, 0);
    } else {
      q.x0.set(x[i] * (y[j] - y[i]) - y[i] * (x[j] - x[i]), y[j] - y[i]);
    }
    // cerr << q.x0 << ' ' << q.d << endl;
    m[q]++;
  }
  l answer = set2(n);
  for (auto p : m) {
    l t = p.second;
    t = round(sqrt(8 * t + 1) + 1) / 2;
    // cerr << p.second << ' ' << t << endl;
    answer = cong(answer - set2(t), MOD);
  }
  cout << answer << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
