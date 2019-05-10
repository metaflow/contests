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

l       popcnt(l value) { return __builtin_popcount(value); }
bool    bit_set(l mask, l i) { return mask & (e0 << i); }
const l MM = 201;
using bits = bitset<MM>;

void solve(istream &in, ostream &out) {
  l            size = 8;
  vector<bits> s;
  l            t = 0;
  bits         full;
  full.flip();
  while (t < MM) {
    // pick bits
    l    left = t;
    l    add = size;
    bits tabu;
    bits z;
    while (left > 0) {
      l    best = -1;
      bits small_mask = full;
      F(i, 0, t) {
        if (tabu[i]) continue;
        bits mask;
        for (auto e : s) {
          if (e[i]) mask |= e;
        }
        if (best < 0 or ((mask ^ (mask & tabu)).count()) <
                            (small_mask ^ (small_mask & tabu)).count()) {
          small_mask = mask;
          best = i;
        }
      }
      if (best < 0) { L(tabu, left, add, small_mask, t); }
      C(best != -1);
      z[best] = 1;
      add--;
      tabu = tabu | small_mask;
      left = t - tabu.count();
    }
    F(i, 0, add) {
      if (t >= MM) break;
      z[t] = 1;
      t++;
    }
    s.emplace_back(z);
    // L(z, t, s.size());
    // if (t <= s.size()) {
    // L("square", t, s.size());
    // }
  }
  l tcc;
  in >> tcc;
  while (tcc--) {
    l n;
    in >> n;
    vvb  z(n, vb(n));
    function<void(l, l)> fill = [&](l a, l k) {
      if (k < MM) {
        F(i, 0, k) {
          F(j, 0, k) {
            z[i + a][j + a] = s[i][j];
          }
        }
        return;
      }
      fill(a, k / 2);
      fill(a + k / 2, k - k / 2);
    };
    fill(0, n);
    F(i, 0, n) {
      F(j, 0, n) {
        out << (z[i][j] ? 'O' : '.');
      }
      out << lf;
    }
  }
}
