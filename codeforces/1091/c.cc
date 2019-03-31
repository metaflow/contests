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
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
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
int  main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7;  // end of template
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

void solve(istream &in, ostream &out) {
  l n;
  in >> n;
  vl   primes;
  auto next_div = sieve_primes(primes);
  auto ff = factorize_to_primes(n, primes, next_div);
  vl   pp;
  l    prev = 0;
  l    c = 0;
  vl   v;
  for (l i : ff) {
    if (i != prev) {
      if (c) {
        pp.emplace_back(c);
        v.emplace_back(prev);
      }
      c = 0;
    }
    prev = i;
    c++;
  }
  if (c) {
    pp.emplace_back(c);
    v.emplace_back(prev);
  }
  l  m = pp.size();
  vl cc(m);
  vl z;
  while (cc.back() <= pp.back()) {
    l x = 1;
    F(i, 0, m) F(j, 0, cc[i]) x *= v[i];
    l k = (n - 1) / x * x + 1;
    l s = n * (k + 1) / x / 2;
    cc[0]++;
    z.emplace_back(s);
    l i = 0;
    while (i + 1 < pp.size() and cc[i] > pp[i]) {
      cc[i] = 0;
      i++;
      cc[i]++;
    }
  }
  sort(all(z));
  bool first = true;
  for (l i : z) {
    if (!first) out << ' ';
    first = false;
    out << i;
  }
  out << lf;
}
