#if defined(LOCAL)
#define PROBLEM_NAME "d"
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

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

const l MAX_PRIME = 5000;
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

bool is_prime(l n, vl& primes) {
  if (n == 1) return false;
  for (auto p : primes) {
    if (n == p) return true;
    if (n % p) return false;
    if (p * p > n) return false;
  }
  return true;
}

void solve(istream& cin, ostream& cout) {
  vl primes;
  sieve_primes(primes);
  l n;
  cin >> n;
  vl v(n); F(i, 0, n) cin >> v[i];
  vvl m(n, vl(n));
  F(i, 0, n) {
    B(j, 0, i + 1) {
      // full cover
      // - holes
      l t = 0;
      F(k, j, i) {
        l d = v[k + 1] - v[k] - 1;
        if (d == 0) continue;
        if (d % 2) {
          if (is_prime(d, primes)) t++; else t += 3;
        } else {
          t += 2;
        }
      }
      // - tail
      l d = v[i] - v[j] + 1;
      if (d % 2) {
        if (is_prime(d, primes)) t++; else t += 3;
      } else {
        t += 2;
      }
      m[j][i] = t;
      F(k, j, i) m[j][i] = min(m[j][i], m[j][k] + m[k + 1][i]);
    }
  }
  cout << m[0][n - 1] << lf;
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
