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

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = 3.1415926;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
using sl = unordered_set<l>;
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

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

  Graph(l n): v(n), e(0) {
    adj.resize(v);
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
struct LCA {  // require 'graph'
  vvl up; // binary lift [i][j] jump of 2^i from j
  vvl hash;
  vl depth; // depth[root] = 0
  LCA(Graph& g) {
    depth.resize(g.v);
    l k = 0;
    while ((1 << k) <= g.v) k++;
    up.resize(k, vl(g.v, -1));
    hash.resize(k, vl(g.v, -1));
  }

  void build_up(l a) {
    F(i, 1, up.size()) {
      l t = up[i - 1][up[i - 1][a]];
      if (t == -1) break;
      up[i][a] = t;
    }
  }

  l walk(l a, l d) {  // walks up d levels
    l k = 0;
    while (d > 0) {
      if (d % 2) a = up[k][a];
      d /= 2;
      k++;
    }
    return a;
  }

  l lca(l a, l b) {
    if (depth[a] < depth[b]) swap(a, b);
    a = walk(a, depth[a] - depth[b]);
    if (a == b) return a;
    B(i, 0, up.size()) {
      if (up[i][a] != up[i][b]) {
        a = up[i][a];
        b = up[i][b];
      }
    }
    a = up[0][a];
    return a;
  }
};

void solve(istream& in, ostream& out) {
  l n, m; in >> n >> m;
  Graph g(n), r(n);
  LCA lca(g);
  string s;
  in >> s;
  F(i, 0, m) {
    l a, b; in >> a >> b; a--; b--;
    g.add_directed(a, b);
    r.add_directed(b, a);
  }
  l source, sink; in >> source >> sink; source--; sink--;
  vb visited(g.v);
  {
   queue<l> q;
   q.emplace(sink);
   visited[sink] = true;
   while (not q.empty()) {
     l a = q.front(); q.pop();
     for (auto e : r.adj[a]) {
       if (visited[e.to]) continue;
       visited[e.to] = true;
       q.emplace(e.to);
     }
   }
  }
  I(visited);
  if (not visited[source]) {
    out << "No way" << lf;
    return;
  }
  vl count(n);
  F(i, 0, n) {
    lca.hash[0][i] = s[i] - 'a' + 1;
    for (auto e : g.adj[i]) {
      if (visited[e.to]) count[i]++;
    }
  }
  I(count);
  Graph z(n);
  {
    queue<l> q;
    q.emplace(sink);
    while (not q.empty()) {
      l a = q.front(); q.pop();
      I(a);
      l best = -1;
      for (auto e : g.adj[a]) {
        if (not visited[e.to]) continue;
        if (best == -1) {
          best = e.to;
          continue;
        }
        l u = e.to, w = best;
        B(k, 0, lca.up.size()) {
          if (lca.up[k][u] == -1) continue;
          if (lca.hash[k][u] == lca.hash[k][w]) {
            u = lca.up[k][u];
            w = lca.up[k][w];
          }
        }
        if (s[u] < s[w]) best = e.to;
      }
      I(best);
      if (best != -1) {
        z.add_directed(a, best);
        lca.up[0][a] = best;
        F(k, 1, lca.up.size()) {
          l t = lca.up[k - 1][lca.up[k - 1][a]];
          l h = lca.hash[k - 1][lca.up[k - 1][a]];
          if (t == -1) break;
          lca.up[k][a] = t;
          lca.hash[k][a] = (h * 1000000 + lca.hash[k - 1][a]) % MOD;
        }
      }
      for (auto e : r.adj[a]) {
        if (not visited[e.to]) continue;
        count[e.to]--;
        if (count[e.to] == 0) q.emplace(e.to);
      }
    }
  }
  l a = source;
  while (true) {
    out << s[a];
    if (a == sink) break;
    a = z.adj[a].back().to;
  }
  out << lf;
}

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
