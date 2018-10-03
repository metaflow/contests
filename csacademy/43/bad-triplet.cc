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
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <limits>
#include <numeric>
#include <queue>
#include <memory>

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>; using sl = unordered_set<l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; const double PI = M_PI;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream& in, ostream& out);
int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false); cin.tie(0);
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

struct Edge {
  l to;
  l from;
  l id;
  // l opposite; // for flow, index in 'to'
  // l capacity; // for flow
  // l cost;
};

struct Graph {
  l v, e; // number of vertices and edges
  vector<vector<Edge>> adj;
  vector<unordered_set<l>> connected_to;

  Graph(l n): v(n), e(0) {
    adj.resize(v);
    connected_to.resize(v);
  }

  l add_node() { adj.resize(++v); return v - 1; }

  void add_simple(l a, l b) { // for tree-like
    Edge ab; ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e++;
    connected_to[a].emplace(b);
    connected_to[b].emplace(a);
  }

  void add_directed(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  //  void add_flow(l a, l b, l w, l cost) {
  // Edge ab; ab.id = e; ab.from = a; ab.to = b; ab.capacity = w; ab.cost = cost;
  // ab.opposite = adj[b].size();
  // Edge ba; ba.id = e; ba.from = b; ba.to = a; ba.capacity = 0; ba.cost = 0;
  // e++;
  // ba.opposite = adj[a].size();
  // adj[a].emplace_back(ab);
  // adj[b].emplace_back(ba);
  // }
};

void print_solution(l a, l b, l c, ostream& out) {
  a++; b++; c++;
  out << a << ' ' << b << ' ' << c << lf;
}

void solve(istream& in, ostream& out) {
  l n, m; in >> n >> m;
  Graph g(n);
  vl d(n);
  F(i, 0, m) {
    l a, b; in >> a >> b; a--; b--;
    g.add_undirected(a, b);
    d[a]++;
    d[b]++;
  }
  l triple = -1;
  l single = -1;
  F(i, 0, n) {
    if (d[i] >= 3) triple = i;
    if (d[i] == 1) single = i;
  }
  if (triple > -1) {
    l a = g.adj[triple][0].to;
    l b = g.adj[triple][1].to;
    l c = g.adj[triple][2].to;
    if (g.connected_to[a].count(b)) {
      print_solution(a, b, triple, out);
      return;
    }
    if (g.connected_to[b].count(c)) {
      print_solution(c, b, triple, out);
      return;
    }
    if (g.connected_to[a].count(c)) {
      print_solution(c, a, triple, out);
      return;
    }
    print_solution(a, b, c, out);
    return;
  }
  if (single != -1 or (m % 3)) {
    out << -1 << lf;
    return;
  }
  // cycle
  m /= 3;
  vl distance(g.v, -1);
  queue<l> q;
  q.emplace(0);
  distance[0] = 0;
  while (not q.empty()) {
    l a = q.front(); q.pop();
    for (auto e : g.adj[a]) {
      if (distance[e.to] > -1) continue;
      distance[e.to] = distance[a] + 1;
      q.emplace(e.to);
    }
  }
  out << 1;
  F(i, 0, n) if (distance[i] == m) out << ' ' << (i + 1);
  out << lf;
}
