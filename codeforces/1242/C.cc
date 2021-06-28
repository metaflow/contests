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
  l n;
  in >> n;
  mll box;
  vvl k(n, vl(0));
  l   sum = 0;
  vl  ksum(n);
  F(i, 0, n) {
    l m;
    in >> m;
    F(j, 0, m) {
      l x;
      in >> x;
      sum += x;
      box[x] = i;
      k[i].emplace_back(x);
      ksum[i] += x;
    }
  }
  if (sum % n) {
    out << "No" << lf;
    return;
  }
  l   target = sum / n;
  L(target);
  vvl st(l1 << n, vl(5000, -1));

  function<l(l, l)> dfs = [&](l mask, l p) -> l {
    if (mask + 1 == st.size()) return 1;
    l i = 0;
    while (mask & (l1 << i)) i++;
    if (p >= k[i].size()) return 0;
    l &z = st[mask][p];
    if (z != -1) return z;
    if (dfs(mask, p + 1)) return z = 1;
    l t = k[i][p];
    l j = i;
    while (true) {
      mask = mask | (l1 << j);
      l b = target - (ksum[j] - t);
      if (box.find(b) == box.end()) return z = 0;
      j = box[b];
      t = b;
      if (mask & (l1 << j)) {
        if (j == i && (k[i][p] == target - (ksum[j] - b))) return dfs(mask, 0);
        return z = 0;
      }
    }
    return z = 0;
  };

  if (!dfs(0, 0)) {
    out << "No" << lf;
    return;
  }

  function<void(l, l)> output = [&](l mask, l p) {
    if (mask + 1 == st.size()) return;
    l i = 0;
    while (mask & (l1 << i)) i++;
    if (p >= k[i].size()) return;
    if (dfs(mask, p + 1)) {
      output(mask, p + 1);
      return;
    }
    l t = k[i][p];
    l j = i;
    while (true) {
      mask = mask | (l1 << j);
      l b = target - (ksum[j] - t);
      out << b << ' ' << j + 1 << lf;
      j = box[b];
      if (mask & (l1 << j)) {
        if (j == i && (k[i][p] == target - (ksum[j] - b))) { output(mask, 0); }
        return;
      }
      t = b;
    }
  };
  out << "Yes" << lf;
  output(0, 0);
}
