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

vl ranks(vl v) {
  l   n = v.size();
  vll c(n);
  F(i, 0, n) {
    c[i].first = v[i];
    c[i].second = i;
  }
  sort(all(c));
  l  r = 0;
  vl z(n);
  F(i, 0, n) {
    if (i > 0 and c[i].first != c[i - 1].first) r++;
    z[c[i].second] = r;
  }
  return z;
}

void solve(istream &in, ostream &out) {
  l n, m;
  in >> n >> m;
  vvl grid(n, vl(m));
  F(i, 0, n) F(j, 0, m) in >> grid[i][j];
  vvl rows(n, vl(m)), cols(n, vl(m));
  vl  max_row(n), max_col(m);
  F(r, 0, n) {
    vl v(m);
    F(c, 0, m) v[c] = grid[r][c];
    auto q = ranks(v);
    F(c, 0, m) {
      rows[r][c] = q[c];
      max_row[r] = max(max_row[r], q[c]);
    }
  }
  F(c, 0, m) {
    vl v(n);
    F(r, 0, n) v[r] = grid[r][c];
    auto q = ranks(v);
    F(r, 0, n) {
      cols[r][c] = q[r];
      max_col[c] = max(max_col[c], q[r]);
    }
  }
  F(r, 0, n) {
    F(c, 0, m) {
      if (c) out << ' ';
      l low = max(rows[r][c], cols[r][c]);
      l high = max(max_row[r] - rows[r][c], max_col[c] - cols[r][c]);
      out << low + high + 1;
    }
    out << lf;
  }
}
