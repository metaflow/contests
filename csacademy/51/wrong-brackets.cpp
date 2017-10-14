#if defined(LOCAL)
#define PROBLEM_NAME "wrong-brackets"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define C(x, ...) ;
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

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
vvl combinations(l n) {
  vvl c(n + 1, vl(n + 1));
  F(i, 0, n + 1) {
    c[i][0] = 1;
    F(j, 1, i + 1) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
    }
  }
  return c;
}

set<string> gen(l a, l b, set<string> v) {
  set<string> z;
  if (a == 0 and b == 0) return v;
  if (a) {
    auto t = gen(a - 1, b, v);
    for (auto s : t) z.emplace("(" + s);
  }
  if (b) {
    auto t = gen(a, b - 1, v);
    for (auto s : t) z.emplace(")" + s);
  }
  return z;
}

l bad(l balance, l open, l close, vector<vvl>& dp, vvl& c) {
  if (balance < 0) return c[open + close][open];
  if (open == 0) return 0;
  if (close == 0) return 1;
  auto& z = dp[balance][open][close];
  if (z == -1) {
    z = bad(balance + 1, open - 1, close, dp, c) +
      bad(balance - 1, open, close - 1, dp, c);
  }
  return z;
}

string build(l balance, l open, l close, l k, vector<vvl>& dp, vvl& c) {
  if (open == 0) {
    string s; F(i, 0, close) s += ')';
    return s;
  }
  if (close == 0) {
    string s; F(i, 0, open) s += '(';
    return s;
  }
  if (balance < 0) {
    // ( ?
    l t= c[open + close - 1][close];
    if (t >= k)
      return "(" + build(balance, open - 1, close, k, dp, c);
    return ")" + build(balance, open, close - 1, k - t, dp, c);
  }
  l t = bad(balance + 1, open - 1, close, dp, c);
  if (t >= k) {
    return "(" + build(balance + 1, open - 1, close, k, dp, c);
  } else {
    return ")" + build(balance - 1, open, close - 1, k - t, dp, c);
  }
}

void solve(istream& cin, ostream& cout) {
  auto c = combinations(60);
  vector<vvl> dp(31, vvl(31, vl(31, -1)));
  // L(bad(0, 4, 4, dp, c));
  l n, k; cin >> n >> k;
  cout << build(0, n, n, k, dp, c) << lf;
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
