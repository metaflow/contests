#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

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

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  bool visited;
  bool in_stack;
  int age, reachable;
  vector<pnode> forward;
  l component;
  l value;
  bool root = true;
  //vector<pedge> backward;
};

l component = 0;

void connect(pnode a, pnode b) {
  a->forward.emplace_back(b);
  b->root = false;
}

void scc_dfs(pnode u, l& age, stack<pnode>& s) {
  age++;
  u->age = u->reachable = age;
  u->visited = true;
  s.push(u);
  u->in_stack = true;
  for (auto v : u->forward) {
    if (!v->visited) scc_dfs(v, age, s);
    if (v->in_stack) u->reachable = min(u->reachable, v->reachable);
  }
  if (u->age == u->reachable) {
    while (true) {
      // do something
      auto v = s.top(); s.pop();
      v->component = component;
      v->in_stack = false;
      if (u == v) break;
    }
    component++;
  }
}

void find_scc(graph& g) {
  l age = 0;
  for (auto u : g) {
    if (not u) continue;
    if (u->visited) continue;
    stack<pnode> s;
    scc_dfs(u, age, s);
  }
}

const l MAX = 5001;

void dfs_value(pnode u) {
  for (auto v : u->forward) {
    v->age = max(v->age, u->age + 1);
    dfs_value(v);
    u->value = u->value ^ v->value;
  }
}

l dfs_best(pnode u) {
  u->visited = true;
  l t = 0;
  for (auto v : u->forward) {
    t += dfs_best(v);
  }
  return max(u->value, t);
}

int main_graph() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n;
  while (cin >> n) {
    vl v(n); F(i, 0, n) cin >> v[i];
    vvb connected(MAX, vb(MAX));
    vector<pnode> g(MAX);
    vl prev(MAX, -1);
    F(i, 0, n) {
      l t = v[i];
      if (not g[t]) {
        g[t] = make_shared<node>();
        g[t]->value = t;
      }
      if (prev[t] != -1) {
        F(j, prev[t] + 1, i) if (not connected[t][v[j]]) {
          connect(g[t], g[v[j]]);
          connected[t][v[j]] = true;
        }
      }
      prev[t] = i;
    }
    component = 0;
    find_scc(g);
    graph cc(component);
    for (auto& u : cc) {
      u = make_shared<node>();
      u->value = 0;
      u->visited = false;
      u->root = true;
    }
    for (auto u : g) {
      if (not u) continue;
      cc[u->component]->value = cc[u->component]->value ^ u->value;
      for (auto w : u->forward) {
        if (w->component != u->component)  {
          connect(cc[u->component], cc[w->component]);
          LOG << u->component << " -> " << w->component << endl;
        }
      }
    }
    for (auto& u : cc) {
      if (u->root) dfs_value(u);
    }
    l total = 0;
    for (auto& u : cc) {
      LOG << u->value << endl;
    }
    for (auto& u : cc) {
      if (not u->root) continue;
      total += dfs_best(u);
    }
    cout << total << lf;
    LOG << "------" << lf;
  }
  return 0;
}

l f(l p, vl& v, vl& first, vl& last, vl& memo) {
  if (p >= (l)v.size()) return 0;
  l& r = memo[p];
  if (r == -1) {
    r = 0;
    vb used(MAX);
    l to = last[v[p]];
    l i = p;
    while (i < to) {
      if (first[v[i]] < p) {
        r = 0;
        break;
      }
      to = max(to, last[v[i]]);
      if (not used[v[i]]) {
        r = r ^ v[i];
        used[v[i]] = true;
      }
      i++;
    }
    if (r) {
      r += f(i, v, first, last, memo);
    }
    r = max(r, f(p + 1, v, first, last, memo));
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n;
  while (cin >> n) {
    vl last(MAX), first(MAX, -1);
    vl v(n);
    F(i, 0, n) {
      cin >> v[i];
      if (first[v[i]] == -1) first[v[i]] = i;
      last[v[i]] = i + 1;
    }
    vl memo(n, -1);
    cout << f(0, v, first, last, memo) << lf;
  }
}
