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
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
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
using vvvb = vector<vvb>;
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l      INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l      e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8, l0 = 0, l1 = 1, l2 = 2;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)

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
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _judge = interactive_judge;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7;  // end of template

void solve(istream &in, ostream &out) {
  l n, m, q;
  in >> n >> m >> q;
  vvl r(n, vl(m));
  F(i, 0, n) {
    string s;
    in >> s;
    F(j, 0, m) r[i][j] = s[j] - '0';
  }
  while (q--) {
    l x1, y1, x2, y2;
    in >> x1 >> y1 >> x2 >> y2;
    x1--;
    y1--;
    l    z = 0;
    auto add = [&](l x1, l y1, l x2, l y2, bool inv) {
      l t = 0;
      F(i, x1, x2) F(j, y1, y2) t += r[i][j];
      if (inv) t = (x2 - x1) * (y2 - y1) - t;
      z += t;
    };
    function<void(l, l, l, l, bool)> fy = [&](l a, l b, l x1, l x2, bool inv) {
      l k = 1;
      while (m * k < b) k *= 2;
      if (k == 1) {
        add(x1, a, x2, b, inv);
        return;
      }
      l t = m * k / 2;
      if (a == 0 and b == m * k) {
        z += t;
        return;
      }
      if (a < t) fy(a, t, x1, x2, inv);
      if (b > t) fy(max(l0, a - t), b - t, x1, x2, !inv);
    };
    function<void(l, l, bool)> fx = [&](l a, l b, bool inv) {
      l k = 1;
      while (n * k < b) k *= 2;
      if (k == 1) {
        fy(y1, y2, a, b, inv);
        return;
      }
      l t = n * k / 2;
      if (a == 0 and b == n * k) {
        // L("add", k, t * (y2 - y1));
        z += t * (y2 - y1);
        return;
      }
      if (a < t) fx(a, t, inv);
      if (b > t) fx(max(a - t, l0), b - t, !inv);
    };
    fx(x1, x2, false);
    out << z << lf;
  }
}
