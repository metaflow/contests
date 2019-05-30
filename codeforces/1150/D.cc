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
const l      INF = numeric_limits<int>::max();
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
const l MAX = 251;
void    solve(istream &in, ostream &out) {
  l n, q;
  in >> n >> q;
  string s;
  in >> s;
  vl v(n);
  F(i, 0, n) v[i] = s[i] - 'a';
  vvl next(26, vl(n, INF));
  next[v.back()][n - 1] = n - 1;
  B(i, 0, n - 1) {
    F(j, 0, 26) next[j][i] = next[j][i + 1];
    next[v[i]][i] = i;
  }
  auto fnext = [&](l i, l p) {
    if (p >= n) return INF;
    return next[i][p];
  };
  vvvl state(MAX, vvl(MAX, vl(MAX, -1)));
  state[0][0][0] = 0;
  vvl                  ss(3);
  function<l(l, l, l)> dp = [&](l x, l y, l z) {
    l &rr = state[x][y][z];
    if (rr != -1) return rr;
    rr = INF;
    if (x > 0) { rr = min(rr, fnext(ss[0][x - 1], dp(x - 1, y, z)) + 1); }
    if (y > 0) { rr = min(rr, fnext(ss[1][y - 1], dp(x, y - 1, z)) + 1); }
    if (z > 0) { rr = min(rr, fnext(ss[2][z - 1], dp(x, y, z - 1)) + 1); }
    return rr;
  };
  while (q--) {
    string op;
    l      p;
    char   c;
    in >> op >> p;
    p--;
    if (op == "+") {
      in >> c;
      ss[p].emplace_back(c - 'a');
    } else {
      switch (p) {
        case 0:
          F(i, 0, ss[1].size() + 1) F(j, 0, ss[2].size() + 1) {
            state[ss[0].size()][i][j] = -1;
          }
          break;
        case 1:
          F(i, 0, ss[0].size() + 1) F(j, 0, ss[2].size() + 1) {
            state[i][ss[1].size()][j] = -1;
          }
          break;
        case 2:
          F(i, 0, ss[0].size() + 1) F(j, 0, ss[1].size() + 1) {
            state[i][j][ss[2].size()] = -1;
          }
          break;
      }
      ss[p].pop_back();
    }
    if (dp(ss[0].size(), ss[1].size(), ss[2].size()) != INF) {
      out << "YES" << lf;
    } else {
      out << "NO" << lf;
    }
  }
}
