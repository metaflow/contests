#if defined(LOCAL)
#define PROBLEM_NAME "C"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
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

mll score;

l grindy(l m) {
  if (score.count(m)) return score[m];
  unordered_set<l> s;
  l i = 1;
  while (true) {
    l j = l(1) << (i - 1);
    if (j > m) break;
    l t = ((j - 1) & m) | (m >> i);
    s.emplace(grindy(t));
    i++;
  }
  l j = 0;
  while (s.count(j)) j++;
  return score[m] = j;
}

void solve(istream& cin, ostream& cout) {
  score[0] = 0;
  l n; cin >> n;
  F(i, 0, 20) L(i, grindy(i));
  vl v(n); F(i, 0, n) cin >> v[i];
  vl primes; vl next_div = sieve_primes(primes);
  unordered_map<l, l> u;
  for (auto x : v) {
    auto ff = factorize_to_primes(x, primes, next_div);
    l prev = 0;
    l c = 0;
    for (auto f : ff) {
      if (f != prev and prev) {
        u[prev] |= 1 << (c - 1);
        c = 0;
      }
      c++;
      prev = f;
    }
    if (prev) u[prev] |= 1 << (c - 1);
  }
  l x = 0;
  for (auto& kv : u) x ^= grindy(kv.second);
  cout << (x ? "Mojtaba" : "Arpa") << lf;
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
