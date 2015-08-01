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

const ll MOD = 10009;

struct node {
  bool visited;
  int level;
  int id;
  int parent;
  ll sum;
  int size;
  ll pending;
  vi adjusted;
};

vector<node> g;

void mark_levels() {
  g[0].level = 1;
  queue<int> q;
  q.emplace(0);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : g[u].adjusted) {
      if (g[v].level) continue;
      g[v].level = g[u].level + 1;
      g[v].parent = u;
      q.emplace(v);
    }
  }
}

int lca(int u, int v) {
  while (g[u].level > g[v].level) u = g[u].parent;
  while (g[v].level > g[u].level) v = g[v].parent;
  while (u != v) {
    u = g[u].parent;
    v = g[v].parent;
  }
  return u;
}

void get_size(int a) {
  g[a].size = 1;
  for (auto u : g[a].adjusted) {
    if (g[u].size) continue;
    get_size(u);
    g[a].size += g[u].size;
  }
}

void add(int u, int v, int delta) {
  int q = lca(u, v);
  ll qsum = g[q].sum;
  vector<pair<int, ll>> p;
  auto t = u;
  ll running = 0;
  while (true) {
    auto &gt = g[t];
    ll d = (delta * (gt.level - g[q].level + 1)) % MOD;
    gt.sum = (gt.sum + (d * gt.size)) % MOD;
    running += gt.size;
    if (t != q) {
      g[gt.parent].sum = (g[gt.parent].sum + delta * running) % MOD;
    }
    for (auto a : gt.adjusted) {
      if (g[a].level < gt.level) continue;
      p.emplace_back(a, d);
      g[a].visited = false;
    }
    if (t == q) break;
    t = gt.parent;
  }
  t = v;
  running = 0;
  while (true) {
    if (t == q) break;
    auto &gt = g[t];
    ll d = delta * (gt.level - g[q].level + 1) % MOD;
    gt.sum = (gt.sum + d * gt.size) % MOD;
    running += gt.size;
    if (t != q) {
      g[gt.parent].sum = (g[gt.parent].sum + delta * running) % MOD;
    }
    for (auto a : gt.adjusted) {
      if (g[a].level < gt.level) continue;
      p.emplace_back(a, d);
      g[a].visited = false;
    }
    t = gt.parent;
  }
  t = u;
  while (t != q) { g[t].visited = true; t = g[t].parent; }
  t = v;
  while (t != q) { g[t].visited = true; t = g[t].parent; }
  g[q].visited = true;
  t = q;
  qsum = (g[q].sum - qsum + MOD) % MOD;
  while (t != 0) {
    t = g[t].parent;
    g[t].sum = (g[t].sum + qsum) % MOD;
  }
  for (auto h : p) {
    if (g[h.first].visited) continue;
    g[h.first].pending = (g[h.first].pending + h.second) % MOD;
  }
}

void update(int u) {
  if (u != 0) update(g[u].parent);
  g[u].sum = (g[u].sum + g[u].pending * g[u].size) % MOD;
  for (auto v : g[u].adjusted) {
    if (g[v].level < g[u].level) continue;
    g[v].pending += g[u].pending;
  }
  g[u].pending = 0;
}

ll query(int a) {
  update(a);
  return g[a].sum;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n; cin >> n;
  g.resize(n);
  for (ll i = 0; i < n; i++) g[i].id = i;
  for (ll i = 0; i < n - 1; i++) {
    ll a, b; cin >> a >> b;
    a--; b--;
    g[a].adjusted.emplace_back(b);
    g[b].adjusted.emplace_back(a);
  }
  mark_levels();
  get_size(0);
  ll m; cin >> m;
  // cout << g[0]->size << endl;
  while (m--) {
    int op, a, b, t;
    cin >> op >> a;
    a--;
    if (op == 1) {
      cin >> b >> t;
      b--;
      add(a, b, t);
    } else {
      cout << query(a) << endl;
    }
  }
}
