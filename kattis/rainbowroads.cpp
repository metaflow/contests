#if defined(LOCAL)
#define PROBLEM_NAME "rainbowroads"
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
  int to;
  int c;
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

  void add_undirected(l a, l b, l c) {
    Edge ab; ab.to = b; ab.c = c;
    adj[a].emplace_back(ab);
    Edge ba; ba.to = a; ba.c = c;
    adj[b].emplace_back(ba);
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

vi frq;
void dfs(Graph& g, l u, l p, l& total, vl& v) {
  fill(all(frq), 0);
  for (auto& e : g.adj[u]) frq[e.c]++;
  for (auto& e : g.adj[u]) {
    if (frq[e.c] < 2) continue;
    if (e.to == p) {
      total++;
      v[u]--;
    } else {
      v[e.to]++;
    }
  }
  for (auto& e : g.adj[u]) {
    if (e.to == p) continue;
    v[e.to] += v[u];
    dfs(g, e.to, u, total, v);
  }
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  Graph g(n);
  frq.resize(n);
  F(i, 0, n - 1) {
    l a, b, c; cin >> a >> b >> c;
    a--; b--; c--;
    g.add_undirected(a, b, c);
  }
  l t = 0;
  vl v(n);
  dfs(g, 0, 0, t, v);
  l answer = 0;
  for (auto i : v) if (i + t == 0) answer++;
  cout << answer << lf;
  // bool first = true;
  F(i, 0, n) if (v[i] + t == 0) {
    cout << i + 1 << lf;
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
