#if defined(LOCAL)
#define PROBLEM_NAME "LuckyCities"
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
  l to;
  l id, from;
};

struct Graph {
  l v_count, e_count;
  vector<vector<Edge>> adj;

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
  }
};

struct G {
  l size;
  l edge_count, time;
  vector<vector<Edge>> adj;
  vl age, lowlink;
  vb in_path, visited, explored_edge, cut_vertex, bridge;
  vl bridges;
  stack<Edge> edge_stack;
  vl value;
  vector<vector<Edge>> component;

  G(l n) {
    size = n;
    adj.resize(size);
    edge_count = 0;
    time = 0;
    age.resize(size, -1);
    lowlink.resize(size);
    in_path.resize(size);
    visited.resize(size);
    value.resize(size);
    cut_vertex.resize(size);
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = edge_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = edge_count; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    edge_count++;
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

  void build_components() {
    explored_edge.clear(); explored_edge.resize(edge_count);
    bridge.clear(); bridge.resize(edge_count);
    F(i, 0, size) if (not visited[i]) dfs_components(i, edge_count);
  }

  l count_odd_cycle_vertexes() {
    l r = 0;
    F(i, 0, component.size()) {
      auto& c = component[i];
      l s = 1;
      value[c.back().from] = i + 1;
      bool bipartite = true;
      B(j, 0, c.size()) {
        if (abs(value[c[j].to]) == i + 1) {
          bipartite = bipartite and (value[c[j].to] == -value[c[j].from]);
        } else {
          value[c[j].to] = -value[c[j].from];
          s++;
        }
      }
      if (not bipartite and s > 1) r += s;
    }
    return r;
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
    bc.age.resize(g.v_count, -1);
    bc.lowlink.resize(g.v_count, -1);
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
    in_path[a] = true;
    lowlink[a] = age[a] = time; time++;
    l forward_count = 0;
    bool root = edge_id == g.e_count;
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

l count_odd_cycle_vertexes(Graph& g, BiComponents& bi) {
  vl value(g.v_count);
  l r = 0;
  F(i, 0, bi.component.size()) {
    auto& c = bi.component[i];
    l s = 1;
    value[c.back().from] = i + 1;
    bool bipartite = true;
    B(j, 0, c.size()) {
      if (abs(value[c[j].to]) == i + 1) {
        bipartite = bipartite and (value[c[j].to] == -value[c[j].from]);
      } else {
        value[c[j].to] = -value[c[j].from];
        s++;
      }
    }
    if (not bipartite and s > 1) r += s;
  }
  return r;
}

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  while (tcc--) {
    l n, m; cin >> n >> m;
    Graph g(n);
    F(i, 0, m) {
      l a, b; cin >> a >> b; a--; b--;
      g.add_undirected(a, b);
    }
    auto bc = BiComponents::build(g);
    cout << count_odd_cycle_vertexes(g, bc) << lf;
  }
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

bool generate_random(l tc, ostream& cout) {
  l max_cases = 10000;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";
  cout << 1 << lf;
  l n = tc / 100 + 1;
  l m = random_in_range(0, n * n);
  vll pairs;
  F(i, 0, m) {
    l a = random_in_range(0, n);
    l b = random_in_range(0, n);
    if (a == b) continue;
    pairs.emplace_back(a, b);
  }
  m = pairs.size();
  cout << n << ' ' << m << lf;
  // cerr << n << ' ' << m << endl;
  for (auto p : pairs) {
    cout << p.first + 1 << ' ' << p.second + 1 << lf;
    // cerr << p.first + 1 << ' ' << p.second + 1 << endl;
  }
  return tc < max_cases;
}

bool solution_checker(istream& input, istream& /* expected */,
                      istream& actual, ostream& out) {
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
