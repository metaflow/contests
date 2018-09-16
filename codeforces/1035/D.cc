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
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <limits>
#include <numeric>

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = 3.1415926;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7; // end of template

const l MAX_PRIME = 50000;
// returns v[i] = smallest prime divisor of i or 1
vl sieve_primes(vl& primes) {
  vl next_div(MAX_PRIME, 1);
  for (l i = 2; i < MAX_PRIME; i++) {
    if (next_div[i] != 1) continue;
    primes.emplace_back(i);
    for (l j = i; j < MAX_PRIME; j += i) if (next_div[j] == 1) next_div[j] = i;
  }
  return next_div;
}

bool is_prime(l n, vl const& primes) {
  auto p = primes.begin();
  while (p != primes.end() and ((*p) * (*p)) <= n) {
    if (n % *p == 0) return n == *p;
    p++;
  }
  return true;
}

// in asc order
vl factorize_to_primes(l n, vl& primes, vl& next_div) {
  auto p = primes.begin();
  vl result;
  while (n >= MAX_PRIME and p != primes.end()) {
    while (n % *p == 0) { result.emplace_back(*p); n /= *p; }
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

bool dfs(l a, l b, vector<vector<unordered_set<l>>>& m, vvb& visited) {
  if (!visited[a][b]) {
    visited[a][b] = true;
    F(j, a, b + 1) {
      bool ok = false;
      for (auto x : m[j][j]) {
        if (a <= j - 1) {
          if (!dfs(a, j - 1, m, visited)) break;
          if (!m[a][j - 1].count(x)) continue;
        }
        if (j + 1 <= b) {
          if (!dfs(j + 1, b, m, visited)) break;
          if (!m[j + 1][b].count(x)) continue;
        }
        for (auto y : m[j][j]) m[a][b].emplace(y);
        break;
      }
    }
  }
  return !m[a][b].empty();
}

void solve(istream& in, ostream& out) {
  vl primes;
  auto next_div = sieve_primes(primes);
  l n; in >> n;
  vl v(n); F(i, 0, n) in >> v[i];
  vector<vector<unordered_set<l>>> m(n, vector<unordered_set<l>>(n));
  vvb visited(n, vb(n));
  F(i, 0, n) {
    auto f = factorize_to_primes(v[i], primes, next_div);
    for (auto x : f) m[i][i].emplace(x);
    visited[i][i] = true;
  }
  out << (dfs(0, n - 1, m, visited) ? "Yes" : "No") << lf;
}

int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false); cin.tie(0);
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
