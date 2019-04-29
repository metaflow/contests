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
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
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

// [1, n]
struct BIT {
  vl tree;
  l  max_p;
  BIT(size_t n) {
    C(n > 0);
    max_p = n;
    tree.resize(n + 1);
  };
  l get(l p) {  // sum of [1, p], O(log(max))
    C(p > 0);
    C(p <= max_p);
    l sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  l get(l from, l to) {  // [from, to]
    return get(to) - get(from - 1);
  }
  // O(log(max))
  void add(l p, l value) {
    C(p > 0);
    C(p <= max_p);
    L("add", p, value);
    while (p <= max_p) {
      tree[p] += value;
      p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  l find(l sum) {
    l mask = max_p;
    while (true) {
      l lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    l p = 0;
    l top = -1;
    while (mask != 0) {
      l m = p + mask;
      if (m <= max_p) {
        if (sum == tree[m]) top = m;
        if (sum > tree[m]) {
          p = m;
          sum -= tree[m];
        }
      }
      mask >>= 1;
    }
    if (sum != 0) return top;
    return p;
  }
};

struct state {
  l from, to, a, b, cost;
};

void solve(istream &in, ostream &out) {
  l tcc = 10;
  F(tc, 0, tcc) {
    l n;
    in >> n;
    vl  v(n);
    mll ov;
    F(i, 0, n) {
      in >> v[i];
      ov[v[i]] = i;
    }
    auto w = v;
    sort(all(w), greater<l>());
    mll ow;
    F(i, 0, n) { ow[w[i]] = i; }
    L(v);
    L(w);
    vector<vector<state>> dp(n + 1, vector<state>(n + 1));
    F(i, 0, n + 1) F(j, 0, n + 1) dp[i][j].cost = -1;
    dp[n][n].cost = 0;
    BIT cost(n + 1);
    F(i, 1, n + 1) cost.add(i, 1);
    F(i, 1, n + 1) L(cost.get(i), i);
    function<l(l, l)> dfs = [&](l a, l b) -> l {
      auto &z = dp[a][b];
      if (z.cost != -1) return z.cost;
      debug_indent();
      auto sg = sg::make_scope_guard(debug_unindent);
      L(a, b);
      z.cost = e9;
      if (a < n) {
        l x = v[a];
        l p = ow[x];
        if (p < b) {
          // That was a backward move.
          L("backward");
          l from = L(cost.get(a + 1), a);
          l to = L(cost.get(p + 1), p);
          F(i, 1, n + 1) L(cost.get(i), i);
          cost.add(p + 1, 1);
          cost.add(a + 1, -1);
          l t = from + to + dfs(a + 1, b);
          L("backward undo");
          cost.add(p + 1, -1);
          cost.add(a + 1, 1);
          if (t < z.cost) {
            z.cost = t;
            z.from = from;
            z.to = to;
            z.a = a + 1;
            z.b = b;
          }
          return z.cost;  // have to do that
        }
        if (p > b) {
          // maybe forward move
          L("maybe forward");
          l from = cost.get(a + 1);
          l to = cost.get(p + 1);
          cost.add(a + 1, -1);
          cost.add(p + 1, 1);
          l t = from + to + dfs(a + 1, b);
          L("forward undo");
          cost.add(a + 1, 1);
          cost.add(p + 1, -1);
          if (t < z.cost) {
            z.cost = t;
            z.from = from;
            z.to = to;
            z.a = a + 1;
            z.b = b;
          }
        }
        if (p == b) {
          L("match");
          l t = I(dfs(a + 1, b + 1));
          if (t < z.cost) {
            z.cost = t;
            z.from = -1;
            z.to = -1;
            z.a = a + 1;
            z.b = b + 1;
          }
        }
      }
      if (b < n) {
        l x = w[b];
        l p = ov[x];
        if (p < a) {
          I("forward");
          // that was a forward move
          z.cost = dfs(a, b + 1);
          z.from = -1;
          z.to = -1;
          z.a = a;
          z.b = b + 1;
          return z.cost;
        }
        if (p > a) {
          L("maybe backward");
          // maybe backward move
          l t = dfs(a, b + 1);
          if (t < z.cost) {
            z.cost = t;
            z.from = -1;
            z.to = -1;
            z.a = a;
            z.b = b + 1;
          }
        }
      }
      return I(z.cost, "best", a, b);
    };
    L(dfs(0, 0));
    l   a = 0, b = 0;
    F(i, 0, n + 1) {
      cerr << i << ' ';
      F(j, 0, n + 1) {
        cerr << dp[i][j].cost << ' ';
      }
      cerr << endl;
    }
    vll z;
    while (a < n or b < n) {
      auto &s = dp[a][b];
      if (s.from != -1) { z.emplace_back(s.from, s.to); }
      a = s.a;
      b = s.b;
      L(a, b);
    }
    out << z.size() << lf;
    for (auto x : z) out << x.first << ' ' << x.second << lf;
#ifdef LOCAL
    break;
#endif
  }
}
