#if defined(LOCAL)
#define PROBLEM_NAME "a"
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
const double EPS = 1e-10; static constexpr double PI = 3.1415926;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7; // end of template

void solve(istream& in, ostream& out) {
  l n, k; in >> n >> k;
  vl left, right;
  F(i, 0, n) {
    l x; in >> x;
    if (x < 0) {
      left.emplace_back(x);
    } else {
      right.emplace_back(x);
    }
  }
  reverse(all(left));
  l best = INF;
  F(i, 0, left.size() + 1) {
    l a = 0;
    if (i) a = -left[i - 1];
    l j = k - i;
    if (j < 0) break;
    if (j > right.size()) continue;
    l b = 0;
    if (j) b = right[j - 1];
    best = min({best, a * 2 + b, 2 * b + a});
  }
  out << best << lf;
}

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  // TODO: infer binary name from args instead of problem name
  F(i, 0, argc) cerr << "arg " << i << ' ' << argv[i] << endl;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
