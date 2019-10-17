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

l longest(vl &s, l x) {
  l z = 0;
  l c = 0;
  for (auto i : s) {
    if (i == x) {
      c++;
      z = max(z, c);
    } else {
      c = 0;
    }
  }
  return z;
}

void solve(istream &in, ostream &out) {
  l n;
  in >> n;
  vvl ss(n);
  vvb present(n, vb(26));
  F(i, 0, n) {
    string s;
    in >> s;
    for (auto c : s) ss[i].emplace_back(c - 'a');
  }
  F(i, 0, n) {
    if (i) F(j, 0, 26) present[i][j] = present[i - 1][j];
    for (l c : ss[i]) present[i][c] = true;
  }
  auto s = ss.back();
  l    z = 0;
  F(i, 0, 26) z = max(z, longest(s, i));
  l pre = 1;
  while (pre < s.size() && s[pre] == s[0]) pre++;
  if (n > 1) {
    l suff = s.size() - 1;
    while (suff > 0 && s[suff - 1] == s.back()) suff--;
    suff = s.size() - suff;
    L(pre, suff);
    // only prefix with another instance
    if (present[n - 2][s[0]]) z = max(z, pre + 1);
    // only suffix with anther instance
    if (present[n - 2][s.back()]) z = max(z, suff + 1);
    if (pre != s.size() and s[0] == s.back() and present[n - 2][s[0]]) {
      // prefix and suffix plus intermediate
      z = max(z, suff + pre + 1);
    }
  }
  function<l(l, l)> max_run = [&](l k, l x) -> l {
    if (k < 0) return 0;
    l z = longest(ss[k], x);
    l m = ss[k].size();
    if (k > 0 and present[k - 1][x]) {
      z = max(z, l1);
      l p = 0;
      while (p < m and ss[k][p] == x) p++;
      l t = m;
      while (t > 0 and ss[k][t - 1] == x) t--;
      t = m - t;
      z = max(z, p + 1);
      z = max(z, t + 1);
      if (p != m) { z = max(z, p + t + 1); }
    }
    if (longest(ss[k], x) == m) {
      l mr = max_run(k - 1, x);
      z = max(z, (mr + 1) * m + mr);
    }
    return z;
  };
  if (pre == s.size() and n > 1) {
    l mr = max_run(n - 2, s[0]);
    z = max(z, (mr + 1) * pre + mr);
  }
  out << z << lf;
}
