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

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
struct node {
  vector<pedge> adjusted;
  bool visited = false;
  vl steps;
};

struct edge {
  pnode from, to;
  vl steps;
  pedge opposite;
  l count;
};

l k;

struct graph {
  vector<pnode> nodes;
  vector<pedge> edges;
};

void connect(graph& g, pnode a, pnode b) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->steps.resize(k); eb->steps.resize(k);
  ea->from = a; ea->to = b; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->opposite = ea;
  g.edges.emplace_back(ea);
  g.edges.emplace_back(eb);
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

void dfs(graph& g, pedge e) {
  e->count = 1;
  auto to = e->to;
  for (auto r : to->adjusted) {
    if (r->to == e->from) continue;
    dfs(g, r);
    F(i, 0, k) e->steps[(i + 1) % k] += r->steps[i];
    e->count += r->count;
  }
  e->steps[0] += e->count;
  F(i, 0, k) e->from->steps[i] += e->steps[i];
}

void bdfs(graph& g, pedge e) {
  auto o = e->opposite;
  auto u = e->from;
  o->count = g.nodes.size() - e->count;
  F(i, 0, k) o->steps[(i + 1) % k] = u->steps[i] - e->steps[i];
  o->steps[0] += o->count;
  F(i, 0, k) o->from->steps[i] += o->steps[i];
  for (auto r : o->from->adjusted) {
    if (r != o) bdfs(g, r);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n >> k) {
    graph g;
    g.nodes.resize(n);
    for (auto& u : g.nodes) {
      u = make_shared<node>();
      u->steps.resize(k, 0);
    }
    F(i, 0, n - 1) {
      l a, b; cin >> a >> b; a--; b--;
      connect(g, g.nodes[a], g.nodes[b]);
    }
    for (auto ei : g.nodes[0]->adjusted) dfs(g, ei);
    for (auto ei : g.nodes[0]->adjusted) bdfs(g, ei);
    l sum = 0;
    for (auto e : g.edges) sum += e->steps[0];
    cout << sum / 2 << '\n';
  }
}
