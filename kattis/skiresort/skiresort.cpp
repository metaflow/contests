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
  l level;
  vector<pnode> up;
  // dominator tree
  l dt_level;
  vector<pnode> dt_up; // up[i] is 2^i away up from this node
  vector<pnode> dt_down;
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

pnode dt_lca(pnode a, pnode b) {
  if (a->dt_level < b->dt_level) swap(a, b);
  while (a->dt_level > b->dt_level) {
    l k = 0;
    while (k + 1 < a->dt_up.size() and a->dt_up[k + 1]->dt_level >= b->dt_level) k++;
    a = a->dt_up[k];
  }
  while (a != b) {
    l k = 0;
    while (k + 1 < a->dt_up.size() and a->dt_up[k + 1] != b->dt_up[k + 1]) k++;
    a = a->dt_up[k];
    b = b->dt_up[k];
  }
  return a;
}

void build_domination_tree(graph& g) {
  l n = g.size();
  vl v(n);
  iota(all(v), 0);
  // bfs?
  sort(all(v), [&](l a, l b) {return g[a]->order < g[b]->order;});
  g[0]->dt_level = 0;
  F(i, 1, n) {
    l j = v[i];
    auto u = g[j]->backward[0];
    F(k, 1, g[j]->backward.size()) {
      u = dt_lca(u, g[j]->backward[k]);
    }
    g[j]->dt_up.emplace_back(u);
    g[j]->dt_level = u->dt_level + 1;
    u->dt_down.emplace_back(g[j]);
    l s = 1;
    auto t = u;
    while (t->dt_up.size() > s) {
      t = t->dt_up[s];
      s *= 2;
      g[j]->dt_up.emplace_back(t);
    }
  }
}

pair<vvb, vvb> build_reachability(graph& g) {
  vector<pnode> special;
  for (auto u : g) {
    F(k, 1, u->backward.size()) {
      special.emplace_back(u->backward[k]);
    }
  }
  l n = g.size();
  l m = special.size();
  vvb from_special(m, vb(n));
  vvb to_special(m, vb(n));
  for (auto u : special) L(u->id, "special");
  F(i, 0, m) {
    queue<pnode> q;
    q.emplace(special[i]);
    while (not q.empty()) {
      auto u = q.front(); q.pop();
      from_special[i][u->id] = true;
      for (auto v : u->forward) q.emplace(v);
    }
    q.emplace(special[i]);
    while (not q.empty()) {
      auto u = q.front(); q.pop();
      to_special[i][u->id] = true;
      for (auto v : u->backward) q.emplace(v);
    }
  }
  return make_pair(move(from_special), move(to_special));
}

void build_uplift(graph& g) {
  queue<pnode> q;
  g[0]->level = 0;
  q.emplace(g[0]);
  while (not q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->forward) {
      if (v->backward[0] != u) continue;
      auto t = u;
      v->up.emplace_back(t);
      v->level = u->level + 1;
      l k = 1;
      while (t->up.size() > k) {
        t = t->up[k];
        v->up.emplace_back(t);
        k *= 2;
      }
      q.emplace(v);
    }
  }
}

// a -> b
bool reachable(pnode a, pnode b, pair<vvb, vvb>& special) {
  auto t = b;
  while (t->level > a->level) {
    l k = 0;
    while (k + 1 < t->up.size() and t->up[k + 1]->level >= a->level) k++;
    t = t->up[k];
  }
  if (a == t) return true;
  auto& from_special = special.first;
  auto& to_special = special.second;
  l m = from_special.size();
  F(i, 0, m) {
    if (to_special[i][a->id] and from_special[i][b->id]) return true;
  }
  return false;
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
  build_uplift(g);
  auto special = build_reachability(g);
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
