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
#include <cassert>
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

void brute(l n, l target) {
  // cout << "brute " << n << ' ' << target << lf;
  vvl v(n, vl(n));
  vl  rows(n), cols(n);

  auto good = [&]() {
    F(i, 0, n) if (rows[i] != target) return false;
    F(i, 0, n) if (cols[i] != target) return false;
    return true;
  };
  function<bool(l, l, l, l, l, l)> f = [&](l vr, l vc, l hr, l hc, l r, l c) {
    if (good()) return true;
    if (r > c) {
      // horizontal
      F(i, hr, n) {
        F(j, ((i == hr) ? hc : 0), n - 1) {
          if (v[i][j] || v[i][j + 1] || rows[i] == target ||
              cols[j] == target || cols[j + 1] == target)
            continue;
          rows[i]++;
          cols[j]++;
          cols[j + 1]++;
          v[i][j] = v[i][j + 1] = (r + c) % 26 + 1;
          if (f(vr, vc, i, j, r, c + 1)) return true;
          v[i][j] = v[i][j + 1] = 0;
          rows[i]--;
          cols[j]--;
          cols[j + 1]--;
        }
      }
    } else {
      // vertical
      F(i, vr, n - 1) {
        F(j, ((i == vr) ? vc : 0), n) {
          if (v[i][j] || v[i + 1][j] || rows[i] == target ||
              rows[i + 1] == target || cols[j] == target)
            continue;
          rows[i]++;
          rows[i + 1]++;
          cols[j]++;
          v[i][j] = v[i + 1][j] = (r + c) % 26 + 1;
          // l("v", i, j);
          if (f(i, j, hr, hc, r + 1, c)) return true;
          v[i][j] = v[i + 1][j] = 0;
          rows[i]--;
          rows[i + 1]--;
          cols[j]--;
        }
      }
    }
    return false;
  };
  if (f(0, 0, 0, 0, 0, 0)) {
    // cout << "OK" << lf;
    F(i, 0, n) {
      F(j, 0, n) {
        if (v[i][j]) cout << char('a' + v[i][j] - 1); else cout << '.';
      }
      cout << lf;
    }
  }
}

void solve(istream &in, ostream &out) {
  // F(i, 1, 1000) {
    // brute(i, 1);
    // brute(i, 2);
    // brute(i, 3);
  // }
  // brute(1000, 3);
  // return;
  l n;
  in >> n;
  if (n < 3) {
    out << -1 << lf;
    return;
  }
  if (n == 3) {
    brute(3, 1);
    return;
  }
  brute(n, 3);
  return;
  vector<string> v(n, string(n, '.'));
  L(v);
  if (n % 3 == 0) {
    l x = 0;
    while (x < n) {
      v[x][x + 1] = 'a';
      v[x][x + 2] = 'a';
      v[x + 1][x] = 'a';
      v[x + 2][x] = 'a';
      x += 3;
    }
    F(i, 0, n) { out << v[i] << lf; }
    return;
  }
  vs fives = {
      "abbc.", "a..cd", "bba.d", "c.acc", "cbbdd",
  };
  vs fours = {
      "aabc",
      "ddbc",
      "bcaa",
      "bcdd",
  };
  F(i, 0, n) {
    if (i * 5 > n) break;
    l j = n - i * 5;
    if (j % 4) continue;
    j /= 4;
    l o = 0;
    F(k, 0, i) {
      F(x, 0, 5) F(y, 0, 5) { v[o + x][o + y] = fives[x][y]; }
      o += 5;
    }
    F(k, 0, j) {
      F(x, 0, 4) F(y, 0, 4) { v[o + x][o + y] = fours[x][y]; }
      o += 4;
    }
  }
  out << -1 << lf;
}
