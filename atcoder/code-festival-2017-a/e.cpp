#if defined(LOCAL)
#define PROBLEM_NAME "e"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#else
#define L(x, ...) (x)
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

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

const l MAX = e5 + 10;
const l MOD = 998244353;
vl fact, pow2;

l c(l n, l k) {
  // L(n, k, fact.size());
  // assert(n < fact.size() and k < fact.size()); // TODO: local asserts with log
  return cong(fact[n] * inverse_mod(cong(fact[k] * fact[n - k], MOD), MOD), MOD);
}

l f(l x, l y, l z) {
  if (x == 0) {
    if (y + z) return 0;
    return 1;
  }
  return c(x + y + z - 1, x - 1);
}

l count(vl& a, vl& b, vl& c, vl& d) {
  l n = a.size();
  if (n == 0) return 0;
  vl two(n + 1), acca(n + 1), accb(n + 1);
  F(i, 0, n) {
    two[i + 1] = two[i] + ((a[i] and b[i]) ? 1 : 0);
    acca[i + 1] = acca[i] + a[i];
    accb[i + 1] = accb[i] + b[i];
  }
  l tc = accumulate(all(c), 0);
  l td = accumulate(all(d), 0);
  l left = 0;
  l z = 0;
  l w = pow2[two[n]];
  F(i, 0, n) {
    left = cong(left + f(tc, acca[i], accb[i]) * inverse_mod(pow2[two[i]], MOD), MOD);
    l right = cong(f(td, acca[n] - acca[i + 1], accb[n] - accb[i + 1]) *
                   inverse_mod(pow2[two[n] - two[i + 1]], MOD), MOD);
    z = cong(z + cong(w * left, MOD) * right, MOD);
  }
  // F(i, 0, n) F(j, i, n) {
    // left = cong(f(tc, acca[i], accb[i]), MOD);
    // l right = f(td, acca[n] - acca[j + 1], accb[n] - accb[j + 1]);
    // z = cong(z + cong(pow2[two[j + 1] - two[i]] * left, MOD) * right, MOD);
  // }
  return z;
}

void solve(istream& cin, ostream& cout) {
  l n, m; cin >> n >> m;
  fact.resize(max(2 * n + m, 2 * m + n));
  fact[0] = 1;
  F(i, 1, fact.size()) fact[i] = (fact[i - 1] * i) % MOD;
  pow2.resize(max(n, m) + 10);
  pow2[0] = 1;
  F(i, 1, pow2.size()) pow2[i] = (pow2[i - 1] * 2) % MOD;
  vl a(n), b(n), c(m), d(m);
  string s;
  cin >> s; F(i, 0, n) a[i] = s[i] - '0';
  cin >> s; F(i, 0, n) b[i] = s[i] - '0';
  cin >> s; F(i, 0, m) c[i] = s[i] - '0';
  cin >> s; F(i, 0, m) d[i] = s[i] - '0';
  vl ca, cb, cc, cd;
  F(i, 0, n) if (a[i] or b[i]) {
    ca.emplace_back(a[i]);
    cb.emplace_back(b[i]);
  }
  F(i, 0, m) if (c[i] or d[i]) {
    cc.emplace_back(c[i]);
    cd.emplace_back(d[i]);
  }
  if (ca.empty() and cc.empty()) {
    cout << 1 << lf;
    return;
  }
  cout << cong(count(cc, cd, ca, cb) + count(cb, ca, cc, cd), MOD) << lf;
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
