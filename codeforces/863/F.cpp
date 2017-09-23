#if defined(LOCAL)
#define PROBLEM_NAME "F"
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
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

// TODO: rewrite in "normal" graph
struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool in_queue;
  l potential;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  l capacity, original_capacity;
  l cost, original_cost;
  pedge opposite;

};

void connect(pnode &a, pnode &b, l w, l cost) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->capacity = ea->original_capacity = w;
  ea->cost = ea->original_cost = cost; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->capacity = eb->original_capacity = 0;
  eb->cost = eb->original_cost = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

void sssp(pnode start, graph& g) {
  for (auto u : g) {
    u->potential = INF;
    u->in_queue = false;
    u->back = NULL;
  }
  queue<pnode> q;
  start->potential = 0;
  start->in_queue = true;
  q.emplace(start);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    u->in_queue = false;
    for (auto e : u->adjusted) {
      if (e->capacity == 0) continue;
      auto v = e->to;
      l t = u->potential + e->cost;
      if (t >= v->potential) continue;
      v->potential = t;
      v->back = e;
      if (v->in_queue) continue;
      v->in_queue = true;
      q.emplace(v);
    }
  }
  // update potentials
  for (auto u : g) {
    for (auto e : u->adjusted) {
      if (e->capacity == 0) continue;
      e->cost += e->from->potential - e->to->potential;
    }
  }
}

l min_cost_max_flow(graph& g, pnode s, pnode t) {
  while (true) {
    sssp(s, g);
    if (t->potential == INF) break;
    // augment
    stack<pedge> a;
    l m = INF;
    auto u = t;
    while (u->back) {
      a.push(u->back);
      m = min(m, u->back->capacity);
      u = u->back->from;
    }
    while (!a.empty()) {
      auto e = a.top(); a.pop();
      e->capacity -= m;
      e->opposite->capacity += m;
    }
  }
  l cost = 0;
  for (auto u : g) {
    for (auto e : u->adjusted) {
      cost += (e->original_capacity - e->capacity) * e->original_cost;
    }
  }
  // TODO: calculate flow as well
  return cost;
}


void solve(istream& cin, ostream& cout) {
  l n, q; cin >> n >> q;
  vl from(n, 1), to(n, n);
  F(i, 0, q) {
    l op, a, b, x; cin >> op >> a >> b >> x;
    a--; b--;
    if (op == 1) F(j, a, b + 1) from[j] = max(from[j], x);
    if (op == 2) F(j, a, b + 1) to[j] = min(to[j], x);
  }
  graph g;
  vector<vector<pnode>> values(n, vector<pnode>(n));
  pnode sink = make_shared<node>();
  pnode source = make_shared<node>();
  g.emplace_back(sink);
  g.emplace_back(source);
  l prev = 0;
  F(j, 0, n) {
    l cost = (j + 1) * (j + 1);
    F(i, 0, n) {
      values[i][j] = make_shared<node>();
      g.emplace_back(values[i][j]);
      connect(values[i][j], sink, 1, cost - prev);
      if (j) {
        connect(values[i][j - 1], values[i][j], n, 0);
      }
    }
    prev = cost;
  }
  F(i, 0, n) {
    auto u = make_shared<node>();
    g.emplace_back(u);
    connect(source, u, 1, 0);
    if (to[i] < from[i]) {
      cout << -1 << lf;
      return;
    }
    F(j, from[i] - 1, to[i]) {
      connect(u, values[j][0], 1, 0);
    }
  }
  cout << min_cost_max_flow(g, source, sink) << lf;
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
