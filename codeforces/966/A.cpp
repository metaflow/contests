#if defined(LOCAL)
#define PROBLEM_NAME "#PROBLEM_NAME"
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

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = 3.1415926;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7; // end of template

void solve(istream& in, ostream& out) {
  l n, m, cl, ce, v;
  in >> n >> m >> cl >> ce >> v;
  vl ladders(cl), elevators(ce);
  F(i, 0, cl) in >> ladders[i];
  F(i, 0, ce) in >> elevators[i];
  l q; in >> q;
  F(qq, 0, q) {
    l best = INF;
    l y1, x1, x2, y2; in >> y1 >> x1 >> y2 >> x2;
    l dy = abs(y1-y2);
    if (dy == 0) best = abs(x1 - x2);
    // ladder
    auto e = upper_bound(all(ladders), x1);
    if (e != ladders.end()) {
      auto x = *e;
      best = min(best, dy + abs(x - x1) + abs(x - x2));
    }
    if (e != ladders.begin()) {
      e--;
      auto x = *e;
      best = min(best, dy + abs(x - x1) + abs(x - x2));
    }
    // elevator
    e = upper_bound(all(elevators), x1);
    if (e != elevators.end()) {
      auto x = *e;
      best = min(best, (dy + v - 1)/v + abs(x - x1) + abs(x - x2));
    }
    if (e != elevators.begin()) {
      e--;
      auto x = *e;
      best = min(best, (dy + v - 1)/v + abs(x - x1) + abs(x - x2));
    }
    out << best << lf;
  }
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
