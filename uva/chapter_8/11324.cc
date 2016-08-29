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
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  bool in_stack;
  int age, reachable, scc_size;
  vector<pedge> forward;
  vector<pedge> backward;
  int value;
  int clique;
};

struct edge {
  pnode from, to;
};

void connect(pnode a, pnode b) {
  pedge e = make_shared<edge>();
  e->from = a; e->to = b;
  a->forward.emplace_back(e);
  b->backward.emplace_back(e);
}

void dfs_scc(pnode u, int& age, stack<pnode>& s) {
  age++;
  u->age = u->reachable = age;
  u->visited = true;
  s.push(u);
  u->in_stack = true;
  for (auto e : u->forward) {
    auto v = e->to;
    if (!v->visited) dfs_scc(v, age, s);
    if (v->in_stack) u->reachable = min(u->reachable, v->reachable);
  }
  if (u->age == u->reachable) {
    u->scc_size = 0;
    while (true) {
      u->scc_size++;
      auto v = s.top(); s.pop();
      v->in_stack = false;
      if (u == v) break;
      for (auto e : v->forward) {
        e->from = u;
        u->forward.emplace_back(e);
      }
      v->forward.clear();
      for (auto e : v->backward) {
        e->to = u;
        u->backward.emplace_back(e);
      }
      v->backward.clear();
    }
    // note lot of u -> u edges
  }
}

int max_scc(graph& g) {
  int age = 0;
  for (auto u : g) {
    if (u->visited) continue;
    stack<pnode> s;
    dfs_scc(u, age, s);
  }
  // now it's DAG
  int m = 0;
  queue<pnode> q;
  for (auto u : g) {
    u->value = 0;
    for (auto e : u->backward) {
      if (e->from == e->to) continue;
      u->value++;
    }
    if (u->value == 0) q.emplace(u);
    u->clique = u->scc_size;
  }
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    m = max(m, u->clique);
    for (auto e : u->forward) {
      auto v = e->to;
      if (u == v) continue;
      v->clique = max(v->clique, v->scc_size + u->clique);
      v->value--;
      if (v->value == 0) q.emplace(v);
    }
  }
  return m;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < n; i++) g[i] = make_shared<node>();
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v; u--; v--;
      connect(g[u], g[v]);
    }
    ll answer = max_scc(g);
    cout << answer << endl;
  }
}

