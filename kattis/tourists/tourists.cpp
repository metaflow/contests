#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "tourists"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct Edge {
  l to;
  l id, from;
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

struct TreeUplift {  // require 'graph'
  vvl up; // binary lift [i][j] jump of 2^i from j
  vl depth; // depth[root] = 0

  TreeUplift(Graph& g, l root) {
    depth.resize(g.v);
    l k = 0;
    while ((1 << k) <= g.v) k++;
    up.resize(k, vl(g.v, -1));

    queue<l> q;
    q.emplace(root);
    depth[root] = 0;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      for (auto b : g.adj[a]) {
        if (b.to == up[0][a]) continue;
        up[0][b.to] = a;
        depth[b.to] = depth[a] + 1;
        build_up(b.to);
        q.emplace(b.to);
      }
    }
  }

  void build_up(l a) {
    F(i, 1, up.size()) {
      l t = up[i - 1][up[i - 1][a]];
      if (t == -1) break;
      up[i][a] = t;
    }
  }

  l walk(l a, l d) {
    l k = 0;
    while (d > 0) {
      if (d % 2) a = up[k][a];
      d /= 2;
      k++;
    }
    return a;
  }

  l lca(l a, l b) {
    a = walk(a, depth[a] - depth[b]);
    b = walk(b, depth[b] - depth[a]);
    if (a == b) return a;
    B(i, 0, up.size()) {
      if (up[i][a] != up[i][b]) {
        a = up[i][a];
        b = up[i][b];
      }
    }
    return up[0][a];
  }
};

struct BiComponents {
  l time;
  vl age, lowlink;
  vb in_path, explored_edge, cut_vertex, bridge;
  stack<Edge> edge_stack;
  vector<vector<Edge>> component; // 2-vertex-connected components

  static BiComponents build(Graph& g) {
    BiComponents bc;
    bc.time = 0;
    bc.age.resize(g.v, -1);
    bc.lowlink.resize(g.v, -1);
    bc.in_path.resize(g.v);
    bc.cut_vertex.resize(g.v);

    bc.explored_edge.resize(g.e);
    bc.bridge.resize(g.e);

    F(i, 0, g.v) {
      if (bc.age[i] == 0) bc.dfs_components(i, g.e, g);
    }
    return bc;
  }

  // edge #id ->a
  void dfs_components(l a, l edge_id, Graph& g) {
    in_path[a] = true;
    lowlink[a] = age[a] = time; time++;
    l forward_count = 0;
    bool root = edge_id == g.e;
    for (auto e : g.adj[a]) {
      if (e.id == edge_id) continue;  // same edge
      if (not explored_edge[e.id]) {
        explored_edge[e.id] = true;
        edge_stack.push(e);
      }
      if (age[e.to] != 0) { // visited
        if (in_path[e.to]) { // back edge
          lowlink[a] = min(lowlink[a], age[e.to]);
        }
      } else { // forward edge
        dfs_components(e.to, e.id, g);
        lowlink[a] = min(lowlink[a], lowlink[e.to]);
        if (root ? (++forward_count > 1) : (lowlink[e.to] >= age[a])) {
          // articulation point
          cut_vertex[a] = true;
          // extract component
          vector<Edge> c;
          while (1) {
            auto t = edge_stack.top(); edge_stack.pop();
            c.emplace_back(t);
            if (t.id == e.id) break;
          }
          component.emplace_back(c);
        }
      }
    }
    if (root) {
      if (not edge_stack.empty()) {
        vector<Edge> c;
        while (not edge_stack.empty()) {
          auto t = edge_stack.top(); edge_stack.pop();
          c.emplace_back(t);
        }
        component.emplace_back(c);
      }
    }
    in_path[a] = false;
  }
};

void solve(istream& cin, ostream& cout) {
  l n;
  cin >> n;
  Graph g(n);
  F(i, 0, n - 1) {
    l a, b; cin >> a >> b; a--; b--;
    g.add_undirected(a, b);
  }
  auto lift = TreeUplift(g, 0);
  l answer = 0;
  F(i, 1, n + 1) for (l j = i + i; j <= n; j += i) {
    l r = lift.lca(i - 1, j - 1);
    answer += lift.depth[i - 1] + lift.depth[j - 1] - 2 * lift.depth[r] + 1;
  }
  cout << answer << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
