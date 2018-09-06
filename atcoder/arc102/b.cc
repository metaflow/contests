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
using vlll = vector<tuple<l,l,l>>;

const l MOD = e9 + 7; // end of template
const l MAX = 20;

void connect(l a, l n, vlll& edges) {
  if (n <= 3) {
    F(i, 0, n) edges.emplace_back(a, MAX, i);
    return;
  }
  if (n % 2) {
    edges.emplace_back(a, MAX, n - 1);
  }
  edges.emplace_back(a, a + 1, 0);
  edges.emplace_back(a, a + 1, n / 2);
  connect(a + 1, n / 2, edges);
}

void solve(istream& in, ostream& out) {
  l n; in >> n;
  vlll edges;
  connect(1, n, edges);
  out << MAX << ' ' << edges.size() << lf;
  for (auto e : edges)
    out << get<0>(e) << ' ' << get<1>(e) << ' ' << get<2>(e) << lf;
}

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
