#if defined(LOCAL)
#define PROBLEM_NAME "C"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x, #x)
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

struct Edge {
  l to;
  l id, from, pos;
  // l opposite; // for flow, index in 'to'
  // l capacity; // for flow
  // l cost;
};

struct Graph {
  l v, e; // number of vertices and edges
  vector<vector<Edge>> adj;
  vector<Edge> edges;

  Graph(l n): v(n), e(0) {
    adj.resize(v);
  }

  l add_node() { adj.resize(++v); return v - 1; }

  void add_simple(l a, l b) { // for tree-like
    Edge ab; ab.to = b; ab.id = e; ab.from = a; ab.pos = adj[a].size();
    adj[a].emplace_back(ab);
    edges.emplace_back(ab);
    e++;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e++;
  }
};

const l MOD = e9 + 7;

// exactly x
l go(l ei, l r, l x, l k, l m, Graph& g, vector<vvl>& dp) {
  // r: 0 - any, 1 - less k, 2 - non k
  auto& z = dp[ei][x][r];
  if (z == -1) {
    z = 0;
    auto& e = g.edges[ei];
    // sibling or e
    auto y = g.adj[e.from][min(g.adj[e.from].size() - 1, e.pos + 1)];
    auto& u = g.adj[e.to];
    F(pass, 0, x + 1) {
      if (pass and y.id == ei) continue;
      l sibling = 1;
      if (y.id != ei) sibling = go(y.id, r, pass, k, m, g, dp);
      F(own, 0, 2) {
        if (own + pass > x) continue;
        if (own and r) continue;
        l left = x - own - pass;
        if (left and u.empty()) continue;
        l down = 1;
        if (u.empty()) {
          if (own) {
            down = 1;
          } else {
            switch (r) {
            case 0:
            case 2: down = m - 1; break;
            case 1: down = k - 1; break;
            }
          }
        } else {
          if (own) {
            down = go(u[0].id, 1, left, k, m, g, dp);
          } else {
            down = ((k - 1) * go(u[0].id, 0, left, k, m, g, dp)) % MOD;
            switch (r) {
            case 0:
            case 2:
              down = (down + (m - k) * go(u[0].id, 2, left, k, m, g, dp)) % MOD;
              break;
            }
          }
        }
        z = (z + down * sibling) % MOD;
      }
    }
  }
  return z;
}

void solve(istream& cin, ostream& cout) {
  l n, m; cin >> n >> m;
  Graph g(n + 1);
  g.add_undirected(0, 1);
  F(i, 0, n - 1) {
    l a, b; cin >> a >> b;
    g.add_undirected(a, b);
  }
  Graph t(n + 1);
  vb visited(n + 1);
  visited[0] = true;
  queue<l> q; q.emplace(0);
  while (not q.empty()) {
    l a = q.front(); q.pop();
    for (auto e : g.adj[a]) {
      if (visited[e.to]) continue;
      t.add_simple(a, e.to);
      visited[e.to] = true;
      q.emplace(e.to);
    }
  }
  l k, x; cin >> k >> x;
  assert(g.e == n);
  vector<vvl> dp(n, vvl(x + 1, vl(3, -1))); // [edge][pick][restriction]
  l answer = 0;
  F(i, 0, x + 1) answer = (answer + go(0, 0, i, k, m, t, dp)) % MOD;
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
