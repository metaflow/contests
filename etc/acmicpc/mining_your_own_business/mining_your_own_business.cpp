#if defined(LOCAL)
#define PROBLEM_NAME "mining_your_own_business"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

struct Edge {
  l to; // TODO: rewrite LCA graph to use edges
  l id, from;
};

struct Graph {
  l size;
  l edge_count, time;
  vector<vector<Edge>> adj;
  vl age, lowlink;
  vb in_path, visited, explored_edge, cut_vertex;
  vl bridges;
  // TODO: add vector of all edges to get by id
  stack<Edge> edge_stack;
  vvl vertex_components;
  l components_count;

  Graph(l n) {
    size = n;
    adj.resize(size);
    edge_count = 0;
    time = 0;
    components_count = 0;
    age.resize(size, -1);
    lowlink.resize(size);
    in_path.resize(size);
    visited.resize(size);
    cut_vertex.resize(size);
    vertex_components.resize(size);
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = edge_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = edge_count; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    edge_count++;
  }

  void mark_component(l a) {
    if (vertex_components[a].empty()
        or vertex_components[a].back() != components_count) {
      vertex_components[a].emplace_back(components_count);
    }
  }

  // edge #id ->a
  void dfs_components(l a, l edge_id) {
    visited[a] = true;
    in_path[a] = true;
    lowlink[a] = age[a] = time; time++;
    l forward_count = 0;
    bool root = edge_id == edge_count;
    for (auto e : adj[a]) {
      if (e.id == edge_id) continue;  // same edge
      if (not explored_edge[e.id]) {
        explored_edge[e.id] = true;
        edge_stack.push(e);
      }
      if (visited[e.to]) {
        if (in_path[e.to]) { // back edge
          lowlink[a] = min(lowlink[a], age[e.to]);
        }
      } else { // forward edge
        dfs_components(e.to, e.id);
        lowlink[a] = min(lowlink[a], lowlink[e.to]);
        if (lowlink[e.to] == age[e.to]) { // bridge
          bridges.emplace_back(e.id);
        }
        if (root ? (++forward_count > 1) : (lowlink[e.to] >= age[a])) {
          // articulation point
          cut_vertex[a] = true;
          // extract component
          while (1) {
            auto t = edge_stack.top(); edge_stack.pop();
            mark_component(t.to); // do something with edge
            mark_component(t.from);
            if (t.id == e.id) break;
          }
          components_count++;
        }
      }
    }
    if (root) {
      if (not edge_stack.empty()) {
        while (not edge_stack.empty()) {
          auto t = edge_stack.top(); edge_stack.pop();
          mark_component(t.to); // do something with edge
          mark_component(t.from);
        }
        components_count++;
      }
    }
    in_path[a] = false;
  }

  void build_components() {
    explored_edge.clear();
    explored_edge.resize(edge_count);
    F(i, 0, size) if (not visited[i]) {
      dfs_components(i, edge_count);
    }
  }
};

void solve(istream& cin, ostream& cout) {
  l n;
  l test_case = 0;
  while (cin >> n, n) {
    test_case++;
    vll edges;
    l m = 0;
    F(i, 0, n) {
      l a, b; cin >> a >> b; a--; b--;
      m = max(m, max(a, b) + 1);
      edges.emplace_back(a, b);
    }
    Graph g(m);
    for (auto e : edges) g.add_undirected(e.first, e.second);
    g.build_components();
    l shafts, ways;
    if (g.components_count == 1) {
      shafts = 2;
      ways = m * (m - 1) / 2;
    } else {
      vl component_cuts(g.components_count);
      vl component_size(g.components_count);
      F(i, 0, m) {
        // L(i, g.vertex_components[i]);
        for (auto j : g.vertex_components[i]) {
          component_size[j]++;
          if (g.cut_vertex[i]) component_cuts[j]++;
        }
      }
      ways = 1;
      shafts = 0;
      F(i, 0, g.components_count) {
        if (component_cuts[i] != 1) continue;
        shafts++;
        ways *= component_size[i] - 1;
      }
    }
    cout << "Case " << test_case << ": " << shafts << ' ' << ways << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
#else
  solve(cin, cout);
#endif
}
