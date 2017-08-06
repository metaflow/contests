#if defined(LOCAL)
#define PROBLEM_NAME "it-takes-a-village"
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
  int to, id, from;
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

struct BiComponents {
  l time;
  vi age, lowlink;
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
        if (root ? (++forward_count > 1) : (lowlink[e.to] >= age[a])) {
          // articulation point
          cut_vertex[a] = true;
          // extract component
          vector<Edge> c;
          while (not edge_stack.empty()) {
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

// [1..n]
struct BIT {
  vi tree;
  l max_p;
  BIT(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  // sum of [1, p], O(log(max))
  l get(l p) {
    l sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  // O(log(max))
  void add(l p, l value) {
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

void walk(Graph& g, l a, vi& pre, vi& post, l& p) {
  pre[a] = p++;
  for (auto e : g.adj[a]) {
    if (pre[e.to] != -1) continue;
    walk(g, e.to, pre, post, p);
  }
  post[a] = p++;
}

void solve(istream& cin, ostream& cout) {
  l n, m, q;
  while (cin >> n >> m, n) {
    cin >> q;
    Graph g(n);
    F(i, 0, m) {
      l a, b; cin >> a >> b; a--; b--;
      g.add_undirected(a, b);
    }
    auto bi = BiComponents::build(g);
    l cut_count = 0;
    vi cut_position(n);
    F(i, 0, n) {
      if (bi.cut_vertex[i]) {
        cut_position[i] = cut_count;
        cut_count++;
      }
    }
    l ts = bi.component.size() + cut_count;
    Graph t(("induced tree size", ts));
    vi pos(n, -1);
    if (bi.cut_vertex[0]) pos[0] = 0;
    B(i, 0, bi.component.size()) {
      auto& c = bi.component[i];
      l cp = i + cut_count;
      for (auto e : c) {
        if (bi.cut_vertex[e.from])
          t.add_undirected(cut_position[e.from], cp);
        if (bi.cut_vertex[e.to])
          t.add_undirected(cut_position[e.to], cp);
        if (pos[e.from] == -1) pos[e.from] = cp;
        if (pos[e.to] == -1) pos[e.to] = cp;
      }
    }
    vi pre(ts, -1), post(ts);
    l p = 1;
    walk(t, pos[0], pre, post, p);
    BIT bit(ts * 2);
    // L("pre", pre, "post", post);
    F(i, 0, q) {
      char c; l a;
      cin >> c >> a; a--; a = pos[a];
      if (c == '?') {
        cout << bit.get(pre[a]) << lf;
      } else {
        l x; cin >> x;
        bit.add(pre[a], x);
        bit.add(post[a], -x);
      }
    }
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
