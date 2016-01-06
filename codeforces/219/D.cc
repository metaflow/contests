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
  vector<pedge> adjusted;
  pedge back;
  l w;
};

struct edge {
  pnode from, to;
  bool opposite;
};

void connect(pnode &a, pnode &b) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->opposite = false;
  eb->from = b; eb->to = a; eb->opposite = true;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

l dfs_from(pnode u) {
  l a = 0;
  u->visited = true;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->visited) continue;
    if (e->opposite) a++;
    a += dfs_from(v);
  }
  return a;
}

void dfs_w(pnode u) {
  u->visited = true;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->visited) continue;
    v->w = u->w + 1;
    if (e->opposite) v->w -= 2;
    dfs_w(v);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    graph g(n);
    for (auto &u : g) {
      u = make_shared<node>();
      u->visited = false;
    }
    for (l i = 0; i < n - 1; i++) {
      l a, b; cin >> a >> b; a--; b--;
      connect(g[a], g[b]);
    }
    g[0]->w = dfs_from(g[0]);
    for (auto u : g) u->visited = false;
    dfs_w(g[0]);
    l best = INF;
    for (auto u : g) best = min(best, u->w);
    bool first = true;
    cout << best << endl;
    for (l i = 0; i < n; i++) {
      if (g[i]->w != best) continue;
      if (!first) cout << " ";
      first = false;
      cout << (i + 1);
    }
    cout << endl;
  }
}
