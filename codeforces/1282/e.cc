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
#include <list>
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

l fh(l a, l b) {
  if (a < b) swap(a, b);
  return a * e6 + b;
}

void solve(istream &in, ostream &out) {
  l tcc;
  in >> tcc;
  F(tc, 0, tcc) {
    L("-----");
    l n;
    in >> n;
    list<l>               v;
    vl                    order;
    vb                    used(n);
    unordered_map<l, vll> m;
    l                     a, b, c;
    in >> a >> b >> c;
    v.emplace_back(a);
    v.emplace_back(b);
    v.emplace_back(c);
    v.emplace_back(a);
    order.emplace_back(0);
    used[0] = true;
    F(i, 1, n - 2) {
      in >> a >> b >> c;
      L(a, b, c);
      m[fh(a, b)].emplace_back(make_pair(c, i));
      m[fh(a, c)].emplace_back(make_pair(b, i));
      m[fh(b, c)].emplace_back(make_pair(a, i));
    }
    auto p = v.begin();
    while (1) {
      auto o = next(p);
      if (o == v.end()) break;
      L(*p, *o);
      if (auto xx = m.find(fh(*p, *o)); xx != m.end()) {
        for (auto x : xx->second) {
          auto [y, e] = x;
          if (used[e]) continue;
          v.insert(o, y);
          L("add", *p, *o, y, e);
          order.emplace_back(e);
          used[e] = true;
          o = p;
          break;
        }
      }
      p = o;
    }
    p = v.begin();
    bool first = true;
    while (1) {
      p = next(p);
      if (p == v.end()) break;
      if (!first) out << ' ';
      first = false;
      out << *p;
    }
    out << endl;
    reverse(all(order));
    first = true;
    for (auto x : order) {
      if (!first) out << ' ';
      first = false;
      out << x + 1;
    }
    out << endl;
  }
}
