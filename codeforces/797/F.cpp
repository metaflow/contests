#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr


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
  int capacity, original_capacity;
  int cost, original_cost;
  pedge opposite;
};

void connect(pnode &a, pnode &b, int w, int cost) {
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

l min_cost_max_flow(graph& g, pnode s, pnode t, l& flow) {
  flow = 0;
  while (true) {
    sssp(s, g);
    if (t->potential == INF) break;
    flow++;
    // augment
    stack<pedge> a;
    int m = numeric_limits<int>::max();
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
  return cost;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vl mouses(n); F(i, 0, n) cin >> mouses[i];
    vll holes(m); F(i, 0, m) cin >> holes[i].first >> holes[i].second;
    l total = 0;
    F(i, 0, m) total += holes[i].second;
    if (total < n) {
      cout << -1 << lf;
      continue;
    }
    l distance = 100;
    while (1) {
      graph g(n + m + 2);
      for (auto& u : g) u = make_shared<node>();
      pnode source = g[n + m], sink = g[n + m + 1];
      F(i, 0, n) connect(source, g[i], 1, 0);
      F(i, 0, m) connect(g[i + n], sink, holes[i].second, 0);
      F(i, 0, n) {
        auto p = lower_bound(all(holes), mouses[i], [&](const ll& a, const l& b) {
              return a.first < b;});
        l k = p - holes.begin();
        for (l j = max((l)0, k - distance); j < min(m, k + distance); j++)
          connect(g[i], g[n + j], 1, abs(mouses[i] - holes[j].first));
      }
      l flow;
      l cost = min_cost_max_flow(g, source, sink, flow);
      if (flow == n) {
        cout << cost << lf;
        break;
      }
      distance *= 2;
    }
  }
}
