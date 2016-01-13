#include<bits/stdc++.h>
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
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  bool in_stack;
  int age, reachable;
  l distance;
  vector<pedge> adj;
  //vector<pedge> backward;
};

struct edge {
  pnode from, to;
  bool used;
  pedge opposite;
};

void connect(pnode a, pnode b) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->used = false;
  ea->from = a; ea->to = b; ea->opposite = eb;
  a->adj.emplace_back(ea);
  eb->used = false;
  eb->from = b; eb->to = a; eb->opposite = ea;
  b->adj.emplace_back(eb);
  //b->backward.emplace_back(e);
}

void scc_dfs(pnode u, int& age, stack<pnode>& s) {
  age++;
  u->age = u->reachable = age;
  u->visited = true;
  s.push(u);
  u->in_stack = true;
  for (auto e : u->adj) {
    if (e->used) continue;
    e->used = true;
    e->opposite->used = true;
    auto v = e->to;
    if (!v->visited) scc_dfs(v, age, s);
    if (v->in_stack) u->reachable = min(u->reachable, v->reachable);
  }
  if (u->age == u->reachable) {
    vector<pnode> component;
    while (true) {
      auto v = s.top(); s.pop();
      component.push_back(v);
      v->in_stack = false;
      if (u == v) break;
    }
    if (component.size() > 1) {
      for (auto v : component) v->distance = 0;
    }
  }
}

void find_scc(graph& g) {
  int age = 0;
  for (auto u : g) {
    if (u->visited) continue;
    stack<pnode> s;
    scc_dfs(u, age, s);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    graph g(n);
    for (auto& u : g) {
      u = make_shared<node>();
      u->distance = INF;
    }
    for (l i = 0; i < n; i++) {
      l a, b; cin >> a >> b; a--; b--;
      connect(g[a], g[b]);
    }
    find_scc(g);
    queue<pnode> q;
    for (auto u : g) {
      u->visited = false;
      if (u->distance == 0) {
        q.push(u);
        u->visited = true;
      }
    }
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      for (auto e : u->adj) {
        auto v = e->to;
        if (v->visited) continue;
        v->visited = true;
        q.push(v);
        v->distance = u->distance + 1;
      }
    }
    for (l i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << g[i]->distance;
    }
    cout << endl;
  }
}
