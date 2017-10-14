#if defined(LOCAL)
#define PROBLEM_NAME "cut-the-tree"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define C(x, ...) ;
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
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const l INF = e9;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

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

tuple<l, l> dfs(Graph& g, l a, l p) {
  l h1 = -1, h2 = -INF, d = INF;
  bool f = true;
  for (auto e : g.adj[a]) {
    if (e.to == p) continue;
    auto t = dfs(g, e.to, a);
    if (f) {
      h1 = get<0>(t);
      d = get<1>(t);
      f = false;
      continue;
    }
    if (get<0>(t) > h1) {
      h2 = h1;
      h1 = get<0>(t);
      d = get<1>(t);
    } else {
      h2 = max(h2, get<0>(t));
    }
  }
  return make_tuple(h1 + 1, min(d, h1 - h2));
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  Graph g(n);
  F(i, 0, n - 1) {
    l a, b; cin >> a >> b; a--; b--;
    g.add_undirected(a, b);
  }

  l x, y;
  {
    vb visited(g.v);
    queue<l> q;
    q.emplace(0);
    visited[0] = true;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      x = a;
      for (auto e : g.adj[a]) {
        if (visited[e.to]) continue;
        visited[e.to] = true;
        q.emplace(e.to);
      }
    }
  }

  {
    vb visited(g.v);
    queue<l> q;
    q.emplace(x);
    visited[x] = true;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      y = a;
      for (auto e : g.adj[a]) {
        if (visited[e.to]) continue;
        visited[e.to] = true;
        q.emplace(e.to);
      }
    }
  }

  auto ax = dfs(g, x, -1);
  auto ay = dfs(g, y, -1);
  L(ax, ay);
  l answer = min(get<0>(ax), get<1>(ax) + get<1>(ay));
  cout << answer << lf;
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
