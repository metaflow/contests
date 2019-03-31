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
  l n;
  in >> n;
  string sa, sb;
  in >> sa >> sb;
  l a, b, ab, k;
  a = b = ab = k = 0;
  F(i, 0, n) {
    if (sa[i] == '1' and sb[i] == '1') {
      ab++;
      continue;
    }
    if (sa[i] == '1') {
      a++;
      continue;
    }
    if (sb[i] == '1') {
      b++;
      continue;
    }
    k++;
  }
  F(i, 0, a + 1) {
    F(j, 0, b + 1) {
      if (abs(i - j) > ab) continue;
      if (abs(i - j) % 2 != ab % 2) continue;
      l t = ab;
      t -= abs(i - j);
      l si = max(i, j) + t / 2 + b - j;
      l sj = max(i, j) + t / 2 + a - i;
      L(i, j, si, sj);
      if ((max(si, sj) <= n / 2) && (L(n - si - sj) == k)) {
        // take i (1, 0), take t/2 + max(0, j - i) (1,1) and all other are (0,0)
        l ta = i;
        l tab = t / 2 + max(l(0), j - i);
        l tb = b - j;
        l tk = n / 2 - ta - tab - tb;
        L(ta, tb, tab, tk);
        vl z;
        F(x, 0, n) {
          if (sa[x] == '1' and sb[x] == '1') {
            if (tab) {
              tab--;
              z.emplace_back(x + 1);
            }
            continue;
          }
          if (sa[x] == '1') {
            if (ta) {
              ta--;
              z.emplace_back(x + 1);
            }
            continue;
          }
          if (sb[x] == '1') {
            if (tb) {
              tb--;
              z.emplace_back(x + 1);
            }
            continue;
          }
          if (tk) {
            tk--;
            z.emplace_back(x + 1);
          }
        }
        I(z);
        bool first = true;
        for (auto x : z) {
          if (!first) out << ' ';
          first = false;
          out << x;
        }
        out << lf;
        return;
      }
    }
  }
  out << -1 << lf;
}
