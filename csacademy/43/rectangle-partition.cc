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
#include <queue>
#include <memory>

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>; using sl = unordered_set<l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; const double PI = M_PI;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream& in, ostream& out);
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
const l MOD = e9 + 7; // end of template

void solve(istream& in, ostream& out) {
  l mx, my, n, m; in >> mx >> my >> n >> m;
  mll x;
  mll y;
  l prev = 0;
  vl xx(n); F(i, 0, n) in >> xx[i]; sort(all(xx));
  for (l t : xx) {
    x[t - prev]++;
    prev = t;
  }
  x[mx - prev]++;
  vl yy(m); F(i, 0, m) in >> yy[i]; sort(all(yy));
  prev = 0;
  for (l t : yy) {
    y[t - prev]++;
    prev = t;
  }
  y[my - prev]++;
  L(x, y);
  l z = 0;
  for (auto kv : x) z += kv.second * y[kv.first];
  out << z << lf;
}
