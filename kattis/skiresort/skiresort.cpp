#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "skiresort"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

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
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  l id, order;
  bool visited;
  vector<pnode> forward;
  vector<pnode> backward;
  // dominating tree
  l level;
  vector<pnode> up; // up[i] is 2^i away up from this node
  vector<pnode> down;
};

void connect(pnode &a, pnode &b) {
  a->forward.emplace_back(b);
  b->backward.emplace_back(a);
}

void toposort(graph g) {
  l n = g.size();
  vl out(n);
  queue<pnode> q;
  l p = n;
  F(i, 0, n) {
    out[i] = g[i]->forward.size();
    if (out[i] == 0) q.emplace(g[i]);
  }
  while (not q.empty()) {
    auto u = q.front(); q.pop();
    u->order = p--;
    for (auto v : u->backward) {
      out[v->id]--;
      if (out[v->id] == 0) q.emplace(v);
    }
  }
}

pnode lca(pnode a, pnode b) {
  if (a->level < b->level) swap(a, b);
  while (a->level > b->level) {
    l k = 0;
    while (k + 1 < a->up.size() and a->up[k + 1]->level >= b->level) k++;
    a = a->up[k];
  }
  while (a != b) {
    l k = 0;
    while (k + 1 < a->up.size() and a->up[k + 1] != b->up[k + 1]) k++;
    a = a->up[k];
    b = b->up[k];
  }
  return a;
}

void build_domination_tree(graph g) {
  l n = g.size();
  vl v(n);
  iota(all(v), 0);
  sort(all(v), [&](l a, l b) {return g[a]->order < g[b]->order;});
  g[0]->level = 0;
  F(i, 1, n) {
    l j = v[i];
    auto u = g[j]->backward[0];
    F(k, 1, g[j]->backward.size()) {
      u = lca(u, g[j]->backward[k]);
    }
    g[j]->up.emplace_back(u);
    g[j]->level = u->level + 1;
    u->down.emplace_back(g[j]);
    l s = 1;
    auto t = u;
    while (t->up.size() > s) {
      t = t->up[s];
      s *= 2;
      g[j]->up.emplace_back(t);
    }
  }
}

void solve(istream& cin, ostream& cout) {
  l N, M, Q;
  cin >> N >> M >> Q;
  graph g(N);
  F(i, 0, N) {
    g[i] = make_shared<node>();
    g[i]->id = i;
  }
  F(i, 0, M) {
    l a, b; cin >> a >> b; a--; b--;
    connect(g[a], g[b]);
  }
  toposort(g);
  build_domination_tree(g);
  /* out dominating tree
  for (auto u : g) {
    cerr << u->id + 1 << ' ' << u->level << ": ";
    for (auto v : u->down) cerr << v->id + 1 << ' ';
    cerr << lf;
    }*/
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
