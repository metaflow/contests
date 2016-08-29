#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool in_queue;
  ll potential;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  ll capacity, original_capacity;
  ll cost, original_cost;
  pedge opposite;

};

void connect(pnode &a, pnode &b, ll w, ll cost) {
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
      ll t = u->potential + e->cost;
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
      if (e->original_capacity == 0) continue;
      e->cost += e->from->potential - e->to->potential;
    }
  }
}

ll min_cost_max_flow(graph& g, pnode s, pnode t) {
  while (true) {
    sssp(s, g);
    if (t->potential == INF) break;
    // augment
    stack<pedge> a;
    ll m = INF;
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
  ll cost = 0;
  for (auto u : g) {
    for (auto e : u->adjusted) {
      cost += (e->original_capacity - e->capacity) * e->original_cost;
    }
  }
  return cost;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m;
  while (cin >> n >> m, n) {
    assert(n <= m);
    graph g(n + m + 2);
    for (auto& u : g) u = make_shared<node>();
    auto s = g[0];
    auto t = g.back();
    for (ll i = 0; i < n; i++) connect(s, g[i + 1], 1, 0);
    for (ll i = 0; i < m; i++) connect(g[n + i + 1], t, 1, 0);
    for (ll i = 0; i < n; i++) {
      for (ll j = 0; j < m; j++) {
        double a; cin >> a;
        ll w = round(a * 100);
        connect(g[i + 1], g[j + n + 1], 1, w);
      }
    }
    double v = min_cost_max_flow(g, s, t);
    cout << fixed << setprecision(2) << round(v / n) / 100 << endl;
  }
}
