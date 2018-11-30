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

bool dfs(l p, l x, vl& v, vl& z, vvb& dp) {
  z[p] = x;
  if (p + 1 >= v.size()) return true;
  if (!dp[p][x]) {
    dp[p][x] = true;
    F(i, 0, 5) {
      if ((v[p] == v[p + 1] and i == x) or
          (v[p] < v[p + 1] and x >= i) or
          (v[p] > v[p + 1] and x <= i)) continue;
      if (dfs(p + 1, i, v, z, dp)) return true;
    }
  }
  return false;
}

void solve(istream &in, ostream &out) {
  l n; in >> n;
  vl v(n); F(i, 0, n) in >> v[i];
  vvb dp(n, vb(5));
  F(i, 0, 5) {
    vl z(n);
    if (dfs(0, i, v, z, dp)) {
      F(j, 0, n) {
        if (j) out << ' ';
        out << z[j] + 1;
      }
      out << lf;
      return;
    }
  }
  out << -1 << lf;
}
