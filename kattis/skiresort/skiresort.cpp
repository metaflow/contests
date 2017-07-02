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
  l id, topo_order;
  vector<pnode> adjusted;
  vector<pnode> backward;
  pnode parent;
  l level;
  vector<pnode> up;
  // l k1, q1;
};

void connect(pnode &a, pnode &b) {
  a->adjusted.emplace_back(b);
  b->backward.emplace_back(a);
  if (not b->parent) b->parent = a;
}

// topo_order is not unique, if edge a -> b, order of a is less
void topological_sort(graph& g) {
  l n = g.size();
  vl out(n);
  queue<pnode> q;
  F(i, 0, n) {
    out[i] = g[i]->adjusted.size();
    if (out[i] == 0) {
      q.emplace(g[i]);
      g[i]->topo_order = n;
    }
  }
  while (not q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->backward) {
      out[v->id]--;
      if (out[v->id] == 0) {
        v->topo_order = u->topo_order - 1;
        q.emplace(v);
      }
    }
  }
}

// for LCA, node.parent points back
void build_binary_lift(graph& g) {
  queue<pnode> q;
  g[0]->level = 0;
  q.emplace(g[0]);
  while (not q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->adjusted) {
      if (v->parent != u) continue;
      v->level = u->level + 1;
      auto t = u;
      v->up.emplace_back(t);
      l k = 0;
      while (t->up.size() > k) {
        t = t->up[k];
        v->up.emplace_back(t);
        k++;
      }
      q.emplace(v);
    }
  }
}

pnode lift(pnode a, l n) {
  l k = 0;
  while (n) {
    if (n % 2) a = a->up[k];
    k++;
    n /= 2;
  }
  return a;
}

pnode lca(pnode a, pnode b) {
  if (a->level < b->level) swap(a, b);
  a = lift(a, a->level - b->level);
  if (a == b) return a;
  for (l k = a->up.size() - 1; k >= 0; k--) {
    if (a->up.size() > k and a->up[k] != b->up[k]) {
      a = a->up[k];
      b = b->up[k];
    }
  }
  return a->up[0];
}

graph build_dominator_tree(graph& g) {
  l n = g.size();
  vl v(n);
  iota(all(v), 0);
  sort(all(v), [&](l a, l b) {return g[a]->topo_order < g[b]->topo_order;});
  graph dt(n);
  F(i, 0, n) {
    dt[i] = make_shared<node>();
    dt[i]->id = i;
  }
  dt[v[0]]->level = 0;
  F(i, 1, n) {
    l j = v[i];
    auto u = dt[g[j]->backward[0]->id];
    F(k, 1, g[j]->backward.size()) {
      u = lca(u, dt[g[j]->backward[k]->id]);
    }
    connect(u, dt[j]);
    dt[j]->level = u->level + 1;
    auto t = u;
    l k = 0;
    dt[j]->up.emplace_back(t);
    while (t->up.size() > k) {
      t = t->up[k];
      dt[j]->up.emplace_back(t);
      k++;
    }
  }
  return dt;
}

void build_reachability(graph& g, vvb& from_special, vvb& to_special) {
  vector<pnode> special;
  for (auto u : g) {
    F(k, 1, u->backward.size()) {
      special.emplace_back(u->backward[k]);
    }
  }
  l n = g.size();
  l m = special.size();
  from_special.resize(n, vb(m));
  to_special.resize(n, vb(m));
  F(i, 0, m) {
    queue<pnode> q;
    q.emplace(special[i]);
    while (not q.empty()) {
      auto u = q.front(); q.pop();
      from_special[u->id][i] = true;
      for (auto v : u->adjusted) q.emplace(v);
    }
    q.emplace(special[i]);
    while (not q.empty()) {
      auto u = q.front(); q.pop();
      to_special[u->id][i] = true;
      for (auto v : u->backward) q.emplace(v);
    }
  }
}

// a -> b
bool reachable(pnode a, pnode b, vvb& from_special, vvb& to_special) {
  if (b->topo_order <= a->topo_order) return false;
  if (b->level > a->level) {
    auto t = lift(b, b->level - a->level);
    if (t == a) return true;
  }
  if (from_special.size()) {
    l m = from_special[0].size();
    F(i, 0, m) {
      if (to_special[a->id][i] and from_special[b->id][i]) return true;
    }
  }
  return false;
}

bool any_reachable(pnode a, vector<pnode>& b, vvb& from_special, vvb& to_special) {
  for (auto t : b) if (reachable(a, t, from_special, to_special)) return true;
  return false;
}

l count_k1(l r_id, l a_id, graph& g, graph& dt,
           vl& tabu_id, vvb& from_special, vvb& to_special) {
  // find first above s (inclusive) that does not reaches any of tabu
  auto t = r_id;
  vector<pnode> tabu;
  for (auto i : tabu_id) tabu.emplace_back(g[i]);
  if (any_reachable(g[t], tabu, from_special, to_special)) {
    t = a_id;
    if (any_reachable(g[t], tabu, from_special, to_special)) return 0;
    l k = dt[t]->up.size() - 1;
    while (k >= 0) {
      if (not any_reachable(g[dt[t]->up[k]->id], tabu, from_special, to_special)) {
        t = dt[t]->up[k]->id;
      }
      k--;
    }
    if (dt[t]->level < dt[r_id]->level) t = r_id;
  }
  return dt[a_id]->level - dt[t]->level + 1;
}

l ways(l K, l Q, graph& g, graph& dt, l root_id,
       vector<pnode>& targets,
       vl& tabu_id,
       vvb& from_special, vvb& to_special) {
  if (K > targets.size()) return 0;
  auto& root = dt[root_id];
  // if (K == 1 and root->q1 == Q) {
    // return root->k1;
  // }
  auto s = targets[0];
  F(i, 1, targets.size()) {
    s = lca(s, targets[i]);
    if (s == root) break;
  }
  // assert(s->level >= root->level);
  if (K == 1) {
    // root->q1 = Q;
    // root->k1 = count_k1(root_id, s->id, g, dt, tabu_id, from_special, to_special);
    // return root->k1;
    return count_k1(root_id, s->id, g, dt, tabu_id, from_special, to_special);
  }
  set<l> predecessors;
  map<l, vector<pnode>> ptargets;
  map<l, vl> results;
  for (auto u : targets) {
    if (s == u) return 0;
    auto t = lift(u, u->level - s->level - 1);
    predecessors.emplace(t->id);
    ptargets[t->id].emplace_back(u);
    if (predecessors.size() > K) return 0;
  }
  // assert(predecessors.size() > 1);
  l free_k = K - predecessors.size();
  if (free_k < 0) return 0;
  for (auto p : predecessors) {
    auto new_tabu = tabu_id;
    for (auto t : predecessors) if (t != p) new_tabu.emplace_back(t);
    F(i, 0, min((l) ptargets[p].size(), free_k + 1)) {
      results[p].emplace_back(ways(i + 1, Q, g, dt, p, ptargets[p], new_tabu,
                                   from_special, to_special));
    }
  }
  // split free K
  l answer = 0;
  l m = predecessors.size();
  vl pp; for (auto p : predecessors) pp.emplace_back(p);
  vl dist(m);
  while (dist.back() <= free_k) {
    l sum = 0;
    F(i, 0, m) sum += dist[i];
    bool ok = sum == free_k;
    if (ok) F(i, 0, m) ok = ok and (dist[i] < results[pp[i]].size());
    if (ok) {
      l t = 1;
      F(i, 0, m) t *= results[pp[i]][dist[i]];
      answer += t;
    }
    l j = 0;
    dist[0]++;
    while (j + 1 < m and dist[j] > free_k) {
      dist[j] = 0;
      j++;
      dist[j]++;
    }
  }
  return answer;
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
  topological_sort(g);
  auto dt = build_dominator_tree(g);
  build_binary_lift(g);
  vvb from_special, to_special;
  build_reachability(g, from_special, to_special);
  F(i, 0, Q) {
    l K, A;
    cin >> K >> A;
    vector<pnode> targets(A);
    F(j, 0, A) {
      l x; cin >> x; x--;
      targets[j] = dt[x];
    }
    vl tabu;
    cout << ways(K, i + 1, g, dt, 0, targets, tabu, from_special, to_special)
         << lf;
  }
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
