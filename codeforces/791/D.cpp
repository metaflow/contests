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
const double EPS = 1e-10;
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
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

struct node {
  vl adjusted;
  bool visited = false;
  vl steps;
};

struct edge {
  l from, to;
  vl steps;
  l opposite;
  l count;
};

l k;

struct graph {
  vector<node> nodes;
  vector<edge> edges;
};

void connect(graph& g, l a, l b) {
  edge ea;
  edge eb;
  l i = g.edges.size();
  ea.steps.resize(k); eb.steps.resize(k);
  ea.from = a; ea.to = b; ea.opposite = i + 1;
  eb.from = b; eb.to = a; eb.opposite = i;
  g.edges.emplace_back(ea);
  g.edges.emplace_back(eb);
  g.nodes[a].adjusted.emplace_back(i);
  g.nodes[b].adjusted.emplace_back(i + 1);
}

void dfs(graph& g, l ei) {
  auto& e = g.edges[ei];
  e.count = 1;
  auto& to = g.nodes[e.to];
  for (l r : to.adjusted) {
    if (g.edges[r].to == e.from) continue;
    dfs(g, r);
    F(i, 0, k) e.steps[(i + 1) % k] += g.edges[r].steps[i];
    e.count += g.edges[r].count;
  }
  e.steps[0] += e.count;
  F(i, 0, k) g.nodes[e.from].steps[i] += e.steps[i];
}

void bdfs(graph& g, l ei) {
  auto& e = g.edges[ei];
  auto& o = g.edges[e.opposite];
  auto& u = g.nodes[o.to];
  o.count = g.nodes.size() - e.count;
  o.steps = u.steps;
  F(i, 0, k) o.steps[(i + 1) % k] = u.steps[i] - e.steps[i];
  o.steps[0] += o.count;
  F(i, 0, k) g.nodes[o.from].steps[i] += o.steps[i];
  for (const auto r : g.nodes[o.from].adjusted) {
    if (r != e.opposite) bdfs(g, r);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n >> k) {
    graph g;
    g.nodes.resize(n);
    for (auto& u : g.nodes) { u.steps.resize(k, 0); }
    F(i, 0, n - 1) {
      l a, b; cin >> a >> b; a--; b--;
      connect(g, a, b);
    }
    for (auto ei : g.nodes[0].adjusted) dfs(g, ei);
    for (auto ei : g.nodes[0].adjusted) bdfs(g, ei);
    l sum = 0;
    for (const auto e : g.edges) sum += e.steps[0];
    cout << sum / 2 << '\n';
  }
}
