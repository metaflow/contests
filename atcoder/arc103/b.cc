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
const double PI = M_PI;
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

struct dot {
  l x, y;
};

void mark(l from, l to, l n, const vl &g, vb &pick) {
  if (n == 0)
    return;
  if (n % 2) {
    pick[from] = true;
    mark(from + 1, to, (n - g[from]) / 2, g, pick);
  } else {
    mark(from + 1, to, n / 2, g, pick);
  }
}

void solve(istream &in, ostream &out) {
  l n;
  in >> n;
  vector<dot> v(n);
  F(i, 0, n) in >> v[i].x >> v[i].y;
  vl s(n);
  F(i, 0, n) s[i] = abs(v[i].x) + abs(v[i].y);
  F(i, 0, n - 1) if ((s[i] + s[i + 1]) % 2) {
    out << -1 << lf;
    return;
  }
  vl d(31);
  if (s[0] % 2 == 0) d.emplace_back(0);
  d[0] = 1;
  {
    l t = 0;
    F(i, 1 - s[0] % 2, d.size()) { d[i] = 1 << t++; }
  }
  const string directions = "RLUD";
  out << d.size() << lf;
  F(i, 0, d.size()) {
    if (i)
      out << ' ';
    out << d[i];
  }
  out << lf;
  F(i, 0, n) {
    l p = 1;
    vl g(d.size());
    l r = s[i];
    B(j, 0, d.size()) {
      g[j] = p;
      r = r - d[j];
      if (r < 0) {
        p = -p;
        r = -r;
      }
    }
    C(r == 0);
    vb marky(d.size());
    l y = abs(v[i].y);
    if (s[i] % 2 == 0) {
      if (y % 2) {
        if (g[1] == -1) swap(g[0], g[1]);
        mark(1, d.size(), y, g, marky);
      } else {
        mark(2, d.size(), y / 2, g, marky);
      }
    } else {
      mark(0, d.size(), abs(v[i].y), g, marky);
    }
    l sx(0), sy(0);
    F(j, 0, d.size()) {
      if (marky[j]) {
        l t = g[j];
        if (v[i].y < 0)
          t = -t;
        out << ((t > 0) ? "U" : "D");
        sy += d[j] * t;
      } else {
        l t = g[j];
        if (v[i].x < 0)
          t = -t;
        out << ((t > 0) ? "R" : "L");
        sx += d[j] * t;
      }
    }
    out << lf;
    C(sx == v[i].x);
    C(sy == v[i].y);
  }
}
