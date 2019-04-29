#if defined(LOCAL)
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#endif
#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using ii = pair<int, int>;
using lu = unsigned long long;
using l = long long;
using vs = vector<string>;
using vii = vector<ii>;
using vl = vector<l>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vlu = vector<lu>;
using ll = pair<l, l>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l      INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l      e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream &in, ostream &out);
void solve_brute(istream &, ostream &);
bool interactive_judge(istream &, istream &, ostream &);
bool generate_random(l, ostream &);
bool solution_checker(istream &, istream &, istream &, ostream &);
int  main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  _generate_random_test = generate_random;
  _solve_brute = solve_brute;
  // _judge = interactive_judge;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7;  // end of template

l gcd(l a, l b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

l lcm(l a, l b) { return a / (gcd(a, b)) * b; }

l sign(l n) {
  if (n < 0) return -1;
  if (n == 0) return 0;
  return 1;
}

// conruent modulo, works for negative
l cong(l x, l mod) { return (x % mod + mod) % mod; }

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

l divup(l a, l b) {  // ceil div
  return (a + b - 1) / b;
}

// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
l extended_euclid(l a, l b, l &x, l &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
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
  F(i, 0, n + 1) {
    c[i][0] = 1;
    F(j, 1, i + 1) { c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod; }
  }
  return c;
}

// l on the ring of MOD
struct lm {
  l raw;
  lm() : raw(0) {}
  lm(l x) : raw(x) {}
  lm(lm const &x) : raw(x.raw) {}
  lm(lm &&x) { swap(*this, x); }
  friend void swap(lm &a, lm &b) { swap(a.raw, b.raw); }
  lm &        operator=(l x) {
    raw = x;
    return *this;
  }
  lm &operator=(lm x) {
    swap(*this, x);
    return *this;
  }
  void operator+=(const lm x) { raw = cong(raw + x.raw, MOD); }
  lm   operator+(const lm x) {
    lm z(*this);
    z += x;
    return z;
  }
  void operator-=(const lm x) { raw = cong(raw - x.raw, MOD); }
  lm   operator-(const lm x) {
    lm z(*this);
    z -= x;
    return z;
  }
  void operator*=(const lm x) { raw = cong(raw * x.raw, MOD); }
  lm   operator*(const lm x) {
    lm z(*this);
    z *= x;
    return z;
  }
  void operator/=(const lm x) {
    raw = cong(raw * inverse_mod(x.raw, MOD), MOD);
  }
  void operator++() { raw = cong(raw + 1, MOD); }
  void operator--() { raw = cong(raw - 1, MOD); }
  lm   operator/(const lm x) {
    lm z(*this);
    z /= x;
    return z;
  }
  lm pow(l exp) const {
    lm r(1);
    lm base(*this);
    while (exp) {
      if (exp % 2) r *= base;
      base *= base;
      exp /= 2;
    }
    return r;
  }
};
using vlm = vector<lm>;
using vvlm = vector<vlm>;
using vvvlm = vector<vvlm>;
ostream &operator<<(ostream &s, const lm &p) { return s << p.raw; }

const l MAX_PRIME = 50000;
// returns v[i] = smallest prime divisor of i or 1
vl sieve_primes(vl &primes) {
  vl next_div(MAX_PRIME, 1);
  for (l i = 2; i < MAX_PRIME; i++) {
    if (next_div[i] != 1) continue;
    primes.emplace_back(i);
    for (l j = i; j < MAX_PRIME; j += i)
      if (next_div[j] == 1) next_div[j] = i;
  }
  return next_div;
}

bool is_prime(l n, vl const &primes) {
  auto p = primes.begin();
  while (p != primes.end() and ((*p) * (*p)) <= n) {
    if (n % *p == 0) return n == *p;
    p++;
  }
  return true;
}

// in asc order
vl factorize_to_primes(l n, vl &primes, vl &next_div) {
  auto p = primes.begin();
  vl   result;
  while (n >= MAX_PRIME and p != primes.end()) {
    while (n % *p == 0) {
      result.emplace_back(*p);
      n /= *p;
    }
    p++;
  }
  if (n >= MAX_PRIME) {
    result.emplace_back(n);
    n = 1;
  }
  while (n != 1) {
    result.emplace_back(next_div[n]);
    n /= next_div[n];
  }
  return result;
}

vvl to_freq(vl &sorted) {
  vvl z(2);
  l   last = 0;
  l   count = 0;
  for (l x : sorted) {
    if (x != last) {
      if (count != 0) {
        z[0].emplace_back(last);
        z[1].emplace_back(count);
      }
      last = x;
      count = 0;
    }
    count++;
  }
  if (count != 0) {
    z[0].emplace_back(last);
    z[1].emplace_back(count);
  }
  return z;
}

default_random_engine source(
    chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() { return random_in_range(0, 2) == 1; }

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) { s += an[random_in_range(0, an.size())]; }
  return s;
}

// return false to stop
bool generate_random(l tc, ostream &out) {
  l max_cases = 10000;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";
  // out << random_in_range(1, tc / 100 + 1) << ' ' << random_in_range(1, tc %
  // 100) << lf;
  out << (tc / 100 + 1) << ' ' << (tc % 100 + 1) << lf;
  return tc < max_cases;
}

void solve_brute(istream &in, ostream &out) {
  l a, b;
  in >> a >> b;
  l z = 0;
  l best = lcm(a, b);
  F(k, 0, lcm(a, b)) {
    l t = lcm(a + k, b + k);
    if (t < best) {
      z = k;
      best = t;
    }
  }
  out << z << lf;
}

l num_divisors(l n, vl &primes, vl &divs) {
  auto p = factorize_to_primes(n, primes, divs);
  auto fq = to_freq(p);
  l    z = 1;
  F(i, 0, fq[1].size()) { z *= (fq[1][i] + 1); }
  return z;
}

void solve(istream &in, ostream &out) {
  vl   primes;
  auto divs = sieve_primes(primes);
  l    a, b;
  in >> a >> b;
  if (a > b) swap(a, b);
  // TODO: remove
  if (a == b) {
    out << 0 << lf;
    return;
  }
  l    z = 0;
  l    best = lcm(a, b);
  auto apply = [&](l k) {
    l t = lcm(a + k, b + k);
    if (t < best or (t == best and k < z)) {
      best = t;
      z = k;
    }
  };
  l    d = b - a;
  auto factors = factorize_to_primes(d, primes, divs);
  auto fq = to_freq(factors);
  l    n = fq[0].size();
  vl   v(n);
  while (1) {
    l j = 0;
    while (j < n and v[j] >= fq[1][j]) j++;
    if (j >= n) break;
    v[j]++;
    while (j > 0) {
      j--;
      v[j] = 0;
    }
    // L(v);
    // TODO: don't output L for random tests
    l t = 1;
    F(i, 0, n) F(e, 0, v[i]) t *= fq[0][i];
    l k = t * divup(b, t) - b;
    apply(k);
  }
  out << z << lf;
}
