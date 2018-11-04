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

void solve(istream &in, ostream &out) {
  l tcc;
  in >> tcc;
  while (tcc--) {
    l n, m, x, y;
    in >> n >> m >> x >> y;
    x--;
    y--;
    l z = (n * m - 1) * (n * m - 2);
    L(z);
    F(i, 0, n) F(j, 0, m) {
      if (i == x && j == y) continue;
      l dv;
      if (i == x) {
        if (y < j) dv = m - y - 2;
        if (y > j) dv = y - 1;
      } else {
        dv = m - 1;
      }
      l dh;
      if (j == y) {
        if (x < i) dh = n - x - 2;
        if (x > i) dh = x - 1;
      } else {
        dh = n - 1;
      }
      l k = i + j;
      l dd1, dd2;
      if (x + y == k) {
        l    t = 0;
        bool take = false;
        F(a, 0, n) {
          l b = k - a;
          if (b < 0 or b >= m) continue;
          t++;
          if (a == i) take = true;
          if (a == x) {
            if (take) break;
            t = 1;
          }
        }
        dd1 = t - 2;
      } else {
        l d1 = min(m - 1, k) - max(k + 1 - n, l(0)) + 1;
        dd1 = d1 - 1;
      }
      k = i - j;
      if (x - y == k) {
        l    t = 0;
        bool take = false;
        F(a, 0, n) {
          l b = a - k;
          if (b < 0 or b >= m) continue;
          t++;
          if (a == i) take = true;
          if (a == x) {
            if (take) break;
            t = 1;
          }
        }
        dd2 = t - 2;
      } else {
        l d2 = min(m - 1, n - 1 - k) - max(-k, l(0)) + 1;
        dd2 = d2 - 1;
      }
      l t = dv + dh + dd1 + dd2;
      L(i, j, dv, dh, dd1, dd2, t);
      z -= t;
    }
    out << z << lf;
  }
}
