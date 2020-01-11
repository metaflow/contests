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
  l n, m;
  in >> n >> m;
  vvl v(n, vl(m));
  F(i, 0, n) {
    string s; in >> s;
    F(j, 0, m) v[i][j] = s[j] == 'X';
  }
  l ddx[4] = {-1, -1, +1, +1};
  l ddy[4] = {-1, +1, -1, +1};
  l dsx[4] = {0, 0, n - 1, n - 1};
  l dsy[4] = {0, m - 1, 0, m - 1};
  vvl w(n + 2, vl(m + 2, e7));
  F(d, 0, 4) {
    vvl a(n + 2, vl(m + 2, 0));
    l x = dsx[d];
    l dx = ddx[d];
    l dy = ddy[d];
    while (x >= 0 and x < n) {
      l y = dsy[d];
      while (y >= 0 and y < m) {
        if (v[x][y]) {
          a[x + 1][y + 1] = min(min(
                                a[x + 1 + dx][y + 1 + dy],
                                a[x + 1 + dx][y + 1]),
                                a[x + 1][y + 1 + dy]) + 1;
        }
        y -= dy;
      }
      x -= dx;
    }
    F(i, 0, n + 2) F(j, 0, m + 2) w[i][j] = min(w[i][j], a[i][j]);
  }
  for (auto e : w) L(e);
  l t = e7;
  F(i, 0, n) {
    F(j, 0, m) {
      if (v[i][j] == 0) continue;
      bool included = false;
      F(x, i - 1, i + 2) F(y, j - 1, j + 2) {
        if (w[i + 1][j + 1] < w[x + 1][y + 1]) included = true;
      }
      if (!included) t = min(t, w[i + 1][j + 1]);
    }
  }
  out << t - 1 << lf;
}
