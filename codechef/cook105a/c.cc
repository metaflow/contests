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

struct Edge {
  l to;
  l from;
  l id;
  l value;
  l score;
  // l opposite; // for flow, index in 'to'
  // l capacity; // for flow
  // l cost;
};

struct Graph {
  l                    v, e;  // number of vertices and edges
  vector<vector<Edge>> adj;
  vector<vector<Edge>> bw;

  Graph(l n) : v(n), e(0) {
    adj.resize(v);
    bw.resize(v);
  }

  l add_node() {
    v++;
    adj.resize(v);
    bw.resize(v);
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

  void add_directed(l a, l b, l value) {
    Edge ab;
    ab.id = adj[a].size();
    ab.from = a;
    ab.to = b;
    ab.value = value;
    ab.score = 0;
    bw[b].emplace_back(ab);
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

void solve(istream &in, ostream &out) {
  l tcc;
  in >> tcc;
  while (tcc--) {
    l n, m;
    in >> n >> m;
    Graph g(n);
    vl    v(n);
    F(i, 0, n) in >> v[i];
    vl o(n);
    F(i, 0, m) {
      l a, b;
      in >> a >> b;
      a--;
      b--;
      if (v[a] == v[b]) continue;
      if (v[a] > v[b]) swap(a, b);
      g.add_directed(a, b, v[b] - v[a]);
      o[a]++;
    }
    queue<l> q;
    F(i, 0, n) if (o[i] == 0) q.emplace(i);
    l z = 1;
    while (not q.empty()) {
      l a = q.front();
      q.pop();
      // sort all incoming edges by value
      sort(all(g.bw[a]),
           [&](const Edge &x, const Edge &y) { return x.value < y.value; });
      // sort all outgoing edges by value
      sort(all(g.adj[a]),
           [&](const Edge &x, const Edge &y) { return x.value < y.value; });
      // update outgoing max scores
      {
        l t = 0;
        B(i, 0, g.adj[a].size()) {
          g.adj[a][i].score = t = max(t, g.adj[a][i].score);
        }
      }
      l y = 0;
      F(i, 0, g.bw[a].size()) {
        while (y < g.adj[a].size() and g.bw[a][i].value >= g.adj[a][y].value)
          y++;
        l from = g.bw[a][i].from;
        l id = g.bw[a][i].id;
        o[from]--;
        if (o[from] == 0) q.emplace(from);
        l score = 1;
        if (y < g.adj[a].size()) { score = g.adj[a][y].score; }
        score++;
        g.adj[from][id].score = score;
        z = max(z, score);
      }
    }
    out << z << lf;
  }
}
