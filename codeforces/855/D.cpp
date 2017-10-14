#if defined(LOCAL)
#define PROBLEM_NAME "D"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define C(x...) ;
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

struct Edge {
  l to;
  l from;
  l t;
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

  void add_directed(l a, l b, l t) {
    Edge ab; ab.from = a; ab.to = b; ab.t = t;
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
  vvl part; // binary lift [i][j] jump of 2^i from j
  vl depth; // depth[root] = 0

  LCA(Graph& g) {
    depth.resize(g.v);
    l k = 0;
    while ((1 << k) <= g.v) k++;
    up.resize(k, vl(g.v, -1));
    part.resize(k, vl(g.v, -1));

    vb root(g.v, true);
    for (auto ee : g.adj) {
      for (auto e : ee) {
        root[e.to] = false;
      }
    }
    queue<l> q;
    F(i, 0, g.v) if (root[i]) {
      q.emplace(i);
      depth[i] = 0;
    }
    C(not q.empty());
    while (not q.empty()) {
      l a = q.front(); q.pop();
      for (auto e : g.adj[a]) {
        up[0][e.to] = a;
        part[0][e.to] = e.t;
        depth[e.to] = depth[a] + 1;
        build_up(e.to);
        q.emplace(e.to);
      }
    }
  }

  void build_up(l a) {
    F(i, 1, up.size()) {
      l t = up[i - 1][up[i - 1][a]];
      if (t == -1) break;
      up[i][a] = t;
      part[i][a] = part[i - 1][a] + part[i - 1][up[i - 1][a]];
    }
  }

  ll walk(l a, l d) {  // walks up d levels
    l k = 0;
    l p = 0;
    while (d > 0) {
      if (d % 2) {
        p += part[k][a];
        a = up[k][a];
      }
      d /= 2;
      k++;
    }
    return make_pair(a, p);
  }

  tuple<l, l, l> lca(l a, l b) {
    l pa, pb;
    tie(a, pa) = walk(a, depth[a] - depth[b]);
    tie(b, pb) = walk(b, depth[b] - depth[a]);
    if (a == b) return (make_tuple(a, pa, pb));
    B(i, 0, up.size()) {
      if (up[i][a] != up[i][b]) {
        pa += part[i][a];
        pb += part[i][b];
        a = up[i][a];
        b = up[i][b];
      }
    }
    pa += part[0][a];
    pb += part[0][b];
    a = up[0][a];
    b = up[0][b];
    if (a != b) a = -1;
    return make_tuple(a, pa, pb);
  }
};

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  Graph g(n);
  F(i, 0, n) {
    l p, t; cin >> p >> t;
    if (p < 1) continue;
    p--;
    g.add_directed(p, i, t);
  }
  LCA lca(g);
  // L(lca.up, lca.part, lca.depth);
  l m; cin >> m;
  F(i, 0, m) {
    l t, a, b; cin >> t >> a >> b; a--; b--; t--;
    bool ok;
    auto r = lca.lca(a, b);
    // L(r);
    if (t) {
      // part
      ok = get<0>(r) != -1 and get<0>(r) != b
        and get<1>(r) == 0
        and get<2>(r) == (lca.depth[b] - lca.depth[get<0>(r)]);
    } else {
      // subtype
      ok = a != b and get<0>(r) == a and get<2>(r) == 0;
    }
    cout << (ok ? "YES" : "NO") << lf;
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
