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
const double PI = 3.14159265358979323846;
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

vl kmp_build_back(const string& p) {
  vl b(p.size());
  l j = -1;
  for (size_t i = 0; i < p.size(); i++) {
    b[i] = j;
    while ((j > -1) and (p[j] != p[i])) j = b[j];
    j++;
  }
  return b;
}

l kmp_search(const string& s, const string& p, const vl& b) {
  l j = 0;
  for (size_t i = 1; i < s.size(); i++) {
    while (j > -1 && p[j] != s[i]) j = b[j];
    j++;
    if (j == l(p.size())) {
      j = b[j];
    }
  }
  return j;
}


void solve(istream &in, ostream &out) {
  string s, t; in >> s >> t;
  auto b = kmp_build_back(t);
  l x = kmp_search(t, t, b);
  string tail;
  F(i, x, t.size()) tail += t[i];
  vl cs(2), ct(2), cz(2);
  for (auto c : s) cs[c - '0']++;
  for (auto c : t) ct[c - '0']++;
  for (auto c : tail) cz[c - '0']++;
  L(tail, cz);
  string z;
  if (ct[0] <= cs[0] && ct[1] <= cs[1]) {
    z = t;
    cs[0] -= ct[0];
    cs[1] -= ct[1];
    while (cs[0] >= cz[0] and cs[1] >= cz[1]) {
      z += tail;
      cs[0] -= cz[0];
      cs[1] -= cz[1];
    }
  }
  F(i, 0, cs[0]) z+='0';
  F(i, 0, cs[1]) z+='1';
  out << z << lf;
}
