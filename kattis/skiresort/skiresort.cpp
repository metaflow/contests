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
  vector<pnode> dt_up;
  // vector<pnode> dt_children;
};

void connect(pnode &a, pnode &b) {
  a->forward.emplace_back(b);
  b->backward.emplace_back(a);
}

void toposort(graph& g) {
  l n = g.size();
  vl out(n);
  queue<pnode> q;
  F(i, 0, n) {
    out[i] = g[i]->forward.size();
    if (out[i] == 0) {
      q.emplace(g[i]);
      g[i]->order = n;
    }
  }
  while (not q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->backward) {
      out[v->id]--;
      if (out[v->id] == 0) {
        v->order = u->order - 1;
        q.emplace(v);
      }
    }
  }
}

pnode dt_lca(pnode a, pnode b) {
  if (a->dt_level < b->dt_level) swap(a, b);
  l k = INF;
  while (a->dt_level > b->dt_level) {
    k = min(k, (l)(a->dt_up.size()) - 1);
    while (k > 0 and a->dt_up[k]->dt_level < b->dt_level) k--;
    a = a->dt_up[k];
  }
  k = INF;
  while (a != b) {
    k = min(k, (l)(a->dt_up.size()) - 1);
    while (k > 0 and a->dt_up[k] == b->dt_up[k]) k--;
    a = a->dt_up[k];
    b = b->dt_up[k];
  }
  return a;
}

void build_domination_tree(graph& g) {
  l n = g.size();
  vl v(n);
  iota(all(v), 0);
  sort(all(v), [&](l a, l b) {return g[a]->order < g[b]->order;});
  g[0]->dt_level = 0;
  F(i, 1, n) {
    l j = v[i];
    auto u = g[j]->backward[0];
    F(k, 1, g[j]->backward.size()) {
      u = dt_lca(u, g[j]->backward[k]);
    }
    g[j]->dt_level = u->dt_level + 1;
    auto t = u;
    l k = 0;
    g[j]->dt_up.emplace_back(t);
    while (t->dt_up.size() > k) {
      t = t->dt_up[k];
      g[j]->dt_up.emplace_back(t);
      if (k) k *= 2; else k++;
    }
  }
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
  from_special.resize(m);
  to_special.resize(m);
  F(i, 0, m) {
    from_special[i].resize(n);
    to_special[i].resize(n);
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
}

void build_uplift(graph& g) {
  queue<pnode> q;
  g[0]->level = 0;
  q.emplace(g[0]);
  while (not q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->forward) {
      if (v->backward[0] != u) continue;
      v->level = u->level + 1;
      auto t = u;
      v->up.emplace_back(t);
      l k = 0;
      while (t->up.size() > k) {
        t = t->up[k];
        v->up.emplace_back(t);
        if (k) k *= 2; else k++;
      }
      q.emplace(v);
    }
  }
}

// a -> b
bool reachable(pnode a, pnode b, vvb& from_special, vvb& to_special) {
  if (b->order <= a->order) return false;
  auto t = b;
  l k = INF;
  while (t->level > a->level) {
    k = min(k, (l)t->up.size() - 1);
    while (k > 0 and t->up[k]->level < a->level) k--;
    t = t->up[k];
  }
  if (a == t) return true;
  l m = from_special.size();
  F(i, 0, m) {
    if (to_special[i][a->id] and from_special[i][b->id]) return true;
  }
  return false;
}

bool any_reachable(pnode a, vector<pnode>& b, vvb& from_special, vvb& to_special) {
  for (auto t : b) if (reachable(a, t, from_special, to_special)) return true;
  return false;
}

// r -> result ~ 0+ ~> a
pnode dt_predecessor(pnode r, pnode a) {
  // assert(a != r);
  l target = r->dt_level + 1;
  l k = INF;
  while (a->dt_level > target) {
    k = min(k, (l)a->dt_up.size() - 1);
    while (k > 0 and a->dt_up[k]->dt_level < target) k--;
    a = a->dt_up[k];
  }
  return a;
}

l ways(l K, graph& g, pnode root,
       vector<pnode>& targets,
       vector<pnode>& tabu,
       vvb& from_special, vvb& to_special) {
  if (K > targets.size()) return 0;
  auto s = targets[0];
  F(i, 1, targets.size()) {
    s = dt_lca(s, targets[i]);
    if (s == root) break;
  }
  // assert(s->level >= root->level);
  if (K == 1) {
    // find first above s (inclusive) that does not reaches any of tabu
    auto t = root;
    if (any_reachable(t, tabu, from_special, to_special)) {
      if (any_reachable(s, tabu, from_special, to_special)) return 0;
      t = s;
      l k = INF;
      while (t != root) {
        k = min(k, (l)(t->dt_up.size() - 1));
        while (k >= 0) {
          if (not any_reachable(t->dt_up[k], tabu, from_special, to_special)) {
            t = t->dt_up[k];
            break;
          }
          k--;
        }
        if (k == -1) break;
      }
      if (t->dt_level < root->dt_level) t = root;
    }
    return s->dt_level - t->dt_level + 1;
  }
  set<l> predecessors;
  map<l, vector<pnode>> ptargets;
  map<l, vl> results;
  for (auto u : targets) {
    if (s == u) return 0;
    auto t = dt_predecessor(s, u);
    predecessors.emplace(t->id);
    ptargets[t->id].emplace_back(u);
    if (predecessors.size() > K) return 0;
  }
  l free_k = K - predecessors.size();
  if (free_k < 0) return 0;
  for (auto p : predecessors) {
    vector<pnode> new_tabu = tabu;
    for (auto t : predecessors) if (t != p) new_tabu.emplace_back(g[t]);
    F(i, 0, min((l) ptargets[p].size(), free_k + 1)) {
      results[p].emplace_back(ways(i + 1, g, g[p], ptargets[p], new_tabu,
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
  toposort(g);
  build_domination_tree(g);
  build_uplift(g);
  vvb from_special, to_special;
  build_reachability(g, from_special, to_special);
  // assert(from_special.size() < 60);
  // if (N > 1000) assert(Q < 50000);
  F(i, 0, Q) {
    l K, A;
    cin >> K >> A;
    vector<pnode> targets(A);
    F(j, 0, A) {
      l x; cin >> x; x--;
      targets[j] = g[x];
    }
    vector<pnode> tabu;
    cout << ways(K, g, g[0], targets, tabu, from_special, to_special) << lf;
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
