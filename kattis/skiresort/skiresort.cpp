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
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct Graph {
  vvl adj;
  vvl par; // [i][j] jump of length 2^i from j, -1 if not defined
  // a -> b, par a is already filled in
  l max_par;
  vl order;
  vl depth;
  Graph(l n) {
    adj.resize(n);
    order.resize(n);
    depth.resize(n);
    max_par = 0;
    while ((1 << max_par) <= n) max_par++;
    par.resize(max_par, vl(n, -1));
  }
  void fill_par(l a) { // assuming par[0][a] is set
    F(i, 1, max_par) {
      par[i][a] = par[i - 1][par[i - 1][a]];
      if (par[i][a] == -1) break;
    }
  }
  l walk(l a, l d) {
    l i = 0;
    while (d > 0) {
      if (d % 2) a = par[i][a];
      d /= 2;
      i++;
    }
    return a;
  }
  l lca(l a, l b) {
    a = walk(a, depth[a] - depth[b]);
    b = walk(b, depth[b] - depth[a]);
    if (a == b) return a;
    B(i, 0, max_par) {
      if (par[i][a] != par[i][b]) {
        a = par[i][a];
        b = par[i][b];
      }
    }
    return par[0][a];
  }
};

Graph build_dt(Graph& g, Graph& r) {
  l n = g.adj.size();
  Graph dt(n);
  vl in_count(n);
  queue<l> q;
  l x = 0;
  F(i, 0, n) {
    in_count[i] = r.adj[i].size();
    if (in_count[i] == 0) {
      dt.depth[i] = 0;
      q.emplace(i);
    }
  }
  assert(q.size());
  while (not q.empty()) {
    l u = q.front(); q.pop();
    g.order[u] = x++;
    if (r.adj[u].size()) {
      l p = r.adj[u][0];
      F(i, 1, r.adj[u].size()) p = dt.lca(p, r.adj[u][i]);
      dt.adj[p].emplace_back(u);
      dt.depth[u] = dt.depth[p] + 1;
      dt.par[0][u] = p;
      dt.fill_par(u);
    }
    for (auto v : g.adj[u]) {
      in_count[v]--;
      if (in_count[v] == 0) q.emplace(v);
    }
  }
  return dt;
}

Graph build_reverse(Graph& g) {
  l n = g.adj.size();
  Graph r(n);
  F(i, 0, n) for (auto j : g.adj[i]) r.adj[j].emplace_back(i);
  return r;
}

void build_special_reachability(Graph& g, Graph& r,
                                vvb& from_special, vvb& to_special) {
  unordered_set<l> special;
  l n = g.adj.size();
  F(i, 0, n) {
    for (auto a : r.adj[i]) {
      if (g.par[0][i] != a) special.insert(a);
    }
  }
  l m = special.size();
  from_special.resize(m, vb(n));
  to_special.resize(m, vb(n));
  vl v;
  for (auto s : special) v.emplace_back(s);
  F(i, 0, m) {
    {
      queue<l> q;
      vb visited(n);
      q.emplace(v[i]);
      visited[v[i]] = true;
      while (not q.empty()) {
        l a = q.front(); q.pop();
        from_special[i][a] = true;
        for (auto b : g.adj[a]) {
          if (visited[b]) continue;
          visited[b] = true;
          q.emplace(b);
        }
      }
    }
    {
      queue<l> q;
      vb visited(n);
      q.emplace(v[i]);
      visited[v[i]] = true;
      while (not q.empty()) {
        l a = q.front(); q.pop();
        to_special[i][a] = true;
        for (auto b : r.adj[a]) {
          if (visited[b]) continue;
          visited[b] = true;
          q.emplace(b);
        }
      }
    }
  }
}

bool reachable(l a, l b, Graph& g, vvb& from_special, vvb& to_special) {
  if (g.order[a] >= g.order[b]) return false;
  l t = g.walk(b, g.depth[b] - g.depth[a]);
  if (t == a) return true;
  l m = from_special.size();
  F(i, 0, m) if (to_special[i][a] and from_special[i][b]) return true;
  return false;
}

bool any_reachable(l a, vl& tabu, Graph& g, vvb& from_special, vvb& to_special) {
  for (auto b : tabu) if (reachable(a, b, g, from_special, to_special)) return true;
  return false;
}

l count_k1(l root, l target, Graph& g, Graph& dt, vl& tabu,
           vvb& from_special, vvb& to_special) {
  l t = root;
  if (any_reachable(root, tabu, g, from_special, to_special)) {
    if (any_reachable(target, tabu, g, from_special, to_special)) return 0;
    t = target;
    B(i, 0, dt.max_par) {
      l x = dt.par[i][t];
      if (x != -1 and not any_reachable(x, tabu, g, from_special, to_special)) {
        t = x;
      }
    }
    // if (dt.depth[t] < dt.depth[root]) t = root;
  }
  return dt.depth[target] - dt.depth[t] + 1;
}

l count_ways(l K, l root, Graph& g, Graph& dt, vl& targets, vl& tabu,
             vvb& from_special, vvb& to_special) {
  if (K > targets.size()) return 0;
  l s = targets[0];
  l m = targets.size();
  F(i, 1, m) s = dt.lca(s, targets[i]);
  if (K == 1) return count_k1(root, s, g, dt, tabu, from_special, to_special);

  map<l, l> part_index;
  vl part_roots;
  vvl part_targets;
  for (auto a : targets) {
    if (a == s) return 0;
    l p = dt.walk(a, dt.depth[a] - dt.depth[s] - 1);
    if (part_index.count(p) == 0) {
      l t = part_index.size();
      if (t == K) return 0;
      part_index[p] = t;
      part_roots.emplace_back(p);
      part_targets.resize(t + 1);
    }
    part_targets[part_index[p]].emplace_back(a);
  }
  l z = part_roots.size();
  l fk = K - z;
  assert(fk >= 0);
  vvl part_results(z);
  F(i, 0, z) {
    vl new_tabu = tabu;
    F(j, 0, z) if (i != j) new_tabu.emplace_back(part_roots[j]);
    l x = min(fk + 1, (l)part_targets[i].size());
    F(j, 0, x) {
      l t = count_ways(j + 1, part_roots[i], g, dt, part_targets[i], new_tabu,
                       from_special, to_special);
      part_results[i].emplace_back(t);
    }
  }
  vl dist(z);
  l answer = 0;
  while (dist.back() <= fk) {
    l sum = accumulate(all(dist), 0);
    if (sum == fk) {
      bool ok = true;
      F(i, 0, z) ok = ok and (dist[i] < part_results[i].size());
      if (ok) {
        l t = 1;
        F(i, 0, z) t *= part_results[i][dist[i]];
        answer += t;
      }
    }
    l i = 0;
    dist[i]++;
    while (i + 1 < z and dist[i] > fk) {
      dist[i] = 0;
      i++;
      dist[i]++;
    }
  }
  return answer;
}

void solve(istream& cin, ostream& cout) {
  l N, M, Q;
  cin >> N >> M >> Q;
  Graph g(N);
  F(i, 0, M) {
    l a, b; cin >> a >> b; a--; b--;
    g.adj[a].emplace_back(b);
    g.par[0][b] = a;
  }
  Graph r = build_reverse(g);
  Graph dt = build_dt(g, r);
  // build lca for g
  queue<l> q;
  q.emplace(0);
  g.depth[0] = 0;
  while (not q.empty()) {
    l u = q.front(); q.pop();
    for (auto v : g.adj[u]) {
      if (g.par[0][v] != u) continue;
      g.depth[v] = g.depth[u] + 1;
      g.fill_par(v);
      q.emplace(v);
    }
  }
  vvb from_special, to_special;
  build_special_reachability(g, r, from_special, to_special);
  F(i, 0, Q) {
    l K, A;
    cin >> K >> A;
    vl targets(A);
    F(j, 0, A) {
      l x; cin >> x; x--;
      targets[j] = x;
    }
    vl tabu;
    cout << count_ways(K, 0, g, dt, targets, tabu, from_special, to_special) << lf;
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
