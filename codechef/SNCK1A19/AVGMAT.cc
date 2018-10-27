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
const double PI = M_PI;
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

void solve(istream &in, ostream &out) {
  l tcc;
  in >> tcc;
  while (tcc--) {
    l n, m;
    in >> n >> m;
    vvl v(n, vl(m));
    F(i, 0, n) {
      string s;
      in >> s;
      F(j, 0, m) v[i][j] = s[j] - '0';
    }
    vl z(n + m - 2);
    {
      vvl d(n + m - 1, vl(n + 1));
      F(i, 0, n) F(j, 0, m) d[i + j][i + 1] = v[i][j];
      F(i, 0, d.size()) F(j, 0, n) d[i][j + 1] += d[i][j];
      F(i, 0, n) F(j, 0, m) {
        if (!v[i][j]) continue;
        F(k, i + j + 1, d.size()) {
          l t = k - i - j;
          z[t - 1] += d[k][min(n, i + t + 1)] - d[k][i];
        }
      }
    }
    {
      vvl d(n + m - 1, vl(n + 1));
      l off = n - 1;
      F(i, 0, n) F(j, 0, m) d[j - i + off][i + 1] = v[i][j];
      L(d);
      F(i, 0, d.size()) F(j, 0, n) d[i][j + 1] += d[i][j];
      F(i, 0, n) F(j, 0, m) {
        if (!v[i][j]) continue;
        F(k, 0, j - i + off) {
          l t = j - i + off - k;
          z[t - 1] += d[k][min(n, i + t)] - d[k][i + 1];
        }
      }
    }
    F(i, 0, z.size()) {
      if (i) out << ' ';
      out << z[i];
    }
    out << lf;
  }
}
