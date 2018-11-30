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
using vvvvl = vector<vvl>;
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
const l MAX = 101;

l dfs(l k, l sum, l p, vl& v, vvvl& dp) {
  if (k == 0) return (sum == 0) ? 1 : 0;
  if (p >= v.size()) return 0;
  l& z = dp[k][sum][p];
  if (z == -1) {
    z = dfs(k, sum, p + 1, v, dp);
    if (z == 0 and v[p] <= sum) z = dfs(k - 1, sum - v[p], p + 1, v, dp);
  }
  return z;
}

void solve(istream &in, ostream &out) {
  l n; in >> n;
  vvvvl dp(n + 1, vvvl(100 * n + 1, vvl(n, vl(MAX, -1))));
  vl v(n); F(i, 0, n) in >> v[i];
  vl c(MAX);
  for (auto x : v) c[x]++;
  l z = 1;
  F(x, 1, MAX) {
    if (c[x] <= z) continue;
    F(k, 1, c[x] + 1) {
      l sum = k * x;
      // L(k, x);
      vb visited(MAX);
      visited[x] = true;
      l found = -1;
      F(i, 0, n) {
        if (visited[v[i]]) continue;
        visited[v[i]] = true;
        if (sum < v[i]) continue;
        found = dfs(k - 1, sum - v[i], i + 1, v, dp);
        if (found) {
          C(found == 1);
          break;
        }
      }
      if (found == 1) break;
      z = max(z, k);
    }
  }
  out << z << lf;
}
