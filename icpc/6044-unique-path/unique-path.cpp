#if defined(LOCAL)
#define PROBLEM_NAME "unique-path"
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
  l to, id, from;
};

struct Graph {
  l v_count, e_count;
  vector<vector<Edge>> adj;
  vector<Edge> edges;

  Graph(l n) {
    v_count = n;
    adj.resize(n);
    e_count = 0;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e_count; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e_count++;
    edges.emplace_back(ab);
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
    bc.age.resize(g.v_count);
    bc.lowlink.resize(g.v_count);
    bc.in_path.resize(g.v_count);
    bc.cut_vertex.resize(g.v_count);

    bc.explored_edge.resize(g.e_count);
    bc.bridge.resize(g.e_count);

    F(i, 0, g.v_count) {
      if (bc.age[i] == 0) bc.dfs_components(i, g.e_count, g);
    }
    return bc;
  }

  // edge #id ->a
  void dfs_components(l a, l edge_id, Graph& g) {
    time++;
    in_path[a] = true;
    lowlink[a] = age[a] = time;
    l forward_count = 0;
    bool root = edge_id == g.e_count;
    for (auto e : g.adj[a]) {
      if (e.id == edge_id) continue;  // same edge
      if (not explored_edge[e.id]) {
        explored_edge[e.id] = true;
        edge_stack.push(e);
      }
      if (age[e.to]) { // visited
        if (in_path[e.to]) { // back edge
          lowlink[a] = min(lowlink[a], age[e.to]);
        }
      } else { // forward edge
        dfs_components(e.to, e.id, g);
        lowlink[a] = min(lowlink[a], lowlink[e.to]);
        bridge[e.id] = lowlink[e.to] == age[e.to];
        if (root ? (++forward_count > 1) : (lowlink[e.to] >= age[a])) {
          cut_vertex[a] = true; // articulation point
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
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    l n, m;
    cin >> n >> m;
    Graph g(n);
    F(i, 0, m) {
      l a, b; cin >> a >> b; a--; b--;
      g.add_undirected(a, b);
    }
    auto bi = BiComponents::build(g);
    vb visited(n);
    F(i, 0, g.e_count) {
      if (bi.bridge[i]) continue;
      visited[g.edges[i].to] = true;
      visited[g.edges[i].from] = true;
    }
    l answer = 0;
    F(i, 0, n) {
      if (visited[i]) continue;
      queue<l> q;
      q.emplace(i);
      visited[i] = true;
      l s = 0;
      while (not q.empty()) {
        s++;
        auto a = q.front(); q.pop();
        for (auto e : g.adj[a]) {
          if (visited[e.to]) continue;
          visited[e.to] = true;
          q.emplace(e.to);
        }
      }
      answer += s * (s - 1) / 2;
    }
    cout << "Case #" << tc << ": " << answer << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
