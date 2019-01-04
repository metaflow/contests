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
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
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
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream &in, ostream &out);
int main(int argc, char **argv) {
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
const l MOD = e9 + 7; // end of template

l dfs(l n, l k, vvl& dp) {
  if (n == 0 and k == 0) return 1;
  l& z = dp[n][k];
  if (z == -1) {
    z = 0;
    F(i, 1, n + 1) {
      l t = i * (i + 1) / 2;
      if (t > k) break;
      if (dfs(n - i, k - t, dp)) {
        z = i;
        break;
      }
    }
  }
  return z;
}

string get_string(l k, l& p, vl& v) {
  string z;
  F(i, 0, v[k]) {
    z += '(';
    if (p < v.size()) {
      p++;
      z += get_string(p - 1, p, v);
    }
    z += ')';
  }
  return z;
}

void solve(istream &in, ostream &out) {
  l tcc; in >> tcc;
  vvl dp(101, vl(e5 + 1, -1));
  F(tc, 0, tcc) {
    l n, k; in >> n >> k;
    if (n % 2) {
      out << "impossible" << lf;
      continue;
    }
    n /= 2;
    vl z;
    do {
      l j = dfs(n, k, dp);
      if (j == 0) break;
      z.emplace_back(j);
      n -= j;
      k -= j * (j + 1) / 2;
    } while (k > 0);
    if (z.empty()) {
      out << "impossible" << lf;
      continue;
    }
    l p = 1;
    out << get_string(0, p, z) << lf;
  }
}
