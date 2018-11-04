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

struct Edge {
  l to;
  l from;
  l id;
  // l opposite; // for flow, index in 'to'
  // l capacity; // for flow
  // l cost;
};

struct Graph {
  l                    v, e;  // number of vertices and edges
  vector<vector<Edge>> adj;

  Graph(l n) : v(n), e(0) { adj.resize(v); }

  l add_node() {
    adj.resize(++v);
    return v - 1;
  }

  void add_simple(l a, l b) {  // for tree-like
    Edge ab;
    ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  void add_undirected(l a, l b) {
    Edge ab;
    ab.id = e;
    ab.from = a;
    ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba;
    ba.id = e;
    ba.from = b;
    ba.to = a;
    adj[b].emplace_back(ba);
    e++;
  }

  void add_directed(l a, l b) {
    Edge ab;
    ab.id = e;
    ab.from = a;
    ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  //  void add_flow(l a, l b, l w, l cost) {
  // Edge ab; ab.id = e; ab.from = a; ab.to = b; ab.capacity = w; ab.cost =
  // cost; ab.opposite = adj[b].size(); Edge ba; ba.id = e; ba.from = b; ba.to =
  // a; ba.capacity = 0; ba.cost = 0; e++; ba.opposite = adj[a].size();
  // adj[a].emplace_back(ab);
  // adj[b].emplace_back(ba);
  // }
};

vvl dfs(l a, l p, Graph& g) {
  vvvl c;
  l h = 0, w = 1;
  for (auto e : g.adj[a]) {
    if (e.to == p) continue;
    c.emplace_back(dfs(e.to, a, g));
    h = max(h, l(c.back().size()));
    w += c.back()[0].size();
  }
  vvl z(h + 1, vl(max(l(1), l(w + c.size()))));
  l off = 1;
  for (auto& r : c) {
    l x = h - r.size() + 1;
    F(i, 0, r.size()) F(j, 0, r[0].size()) {
      z[i + x][j + off] = 1 - r[i][j];
    }
    off += r[0].size() + 1;
  }
  return z;
}

void solve(istream &in, ostream &out) {
  l n, m;
  in >> n >> m;
  if (m != n - 1) {
    out << -1 << lf;
    return;
  }
  Graph g(n);
  F(i, 0, m) {
    l a, b;
    in >> a >> b;
    a--;
    b--;
    L(a, b);
    g.add_undirected(a, b);
  }
  l        t = n;
  vl       age(g.v);
  queue<l> q;
  q.emplace(0);
  t--;
  age[0] = 1;
  while (not q.empty()) {
    l a = q.front();
    q.pop();
    for (auto e : g.adj[a]) {
      if (age[e.to] > 0) continue;
      age[e.to] = age[a] + 1;
      t--;
      q.emplace(e.to);
    }
  }
  if (t) {
    out << -1 << lf;
    return;
  }
  auto z = dfs(0, -1, g);
  out << z.size() << ' ' << z[0].size() << lf;
  C(z.size() * z[0].size() < e5);
  F(i, 0, z.size()) {
    for (auto x : z[i]) out << x;
    out << lf;
  }
}
