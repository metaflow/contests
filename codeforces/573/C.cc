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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  vector<pedge> adjusted;
  ll k = 0;
  ll id, leafs = 0, depth = 0;
  bool top;
  pedge to_parent;
};

struct edge {
  pnode to, from;
  ll leafs = 0;
  pedge opposite;
};

void connect(pnode &a, pnode &b) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
  a->k++;
  b->k++;
}

ll dfs(pnode u) {
  u->visited = true;
  int l = 0;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->visited) continue;
    v->to_parent = e;
    e->leafs = dfs(v);
    l += e->leafs;
  }
  return max(1, l);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vector<pnode> g(n);
    for (ll i = 0; i < n; i++) {
      g[i] = make_shared<node>();
      g[i]->id = i + 1;
    }
    for (ll i = 0; i < n - 1; i++) {
      ll a, b; cin >> a >> b; a--; b--;
      connect(g[a], g[b]);
    }
    ll leafs;
    queue<pnode> q;
    for (auto u : g) {
      if (u->adjusted.size() == 1) {
        q.emplace(u);
        u->visited = true;
        u->leafs = 1;
      }
    }
    leafs = q.size();
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->visited) continue;
        e->opposite->leafs = u->leafs;
        v->leafs += u->leafs;
        v->k--;
        if (v->k == 1) {
          q.emplace(v);
          v->visited = true;
        }
      }
    }
    for (auto u : g) {
      ll big = 0;
      u->visited = false;
      for (auto e : u->adjusted) {
        if (e->leafs == 0) e->leafs = leafs - u->leafs;
        if (e->leafs > 1) big++;
      }
      u->top = (u->adjusted.size() > 3 || big > 1);
    }
    pnode bottom;
    g[0]->visited = true;
    g[0]->depth = 0;
    q.emplace(g[0]);
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->visited) continue;
        v->visited = true;
        v->depth = u->depth + 1;
        v->to_parent = e;
        if (v->top) bottom = v;
        q.emplace(v);
      }
    }
    bool ok = true;
    for (auto u : g) u->visited = false;
    if (bottom) {
      while (bottom->to_parent) {
        bottom->visited = true;
        bottom = bottom->to_parent->from;
      }
      bottom->visited = true;
      bottom.reset();
      for (auto u : g) {
        if (!u->top || u->visited) continue;
        if (!bottom || u->depth > bottom->depth) bottom = u;
      }
      if (bottom) {
        while (!bottom->visited) {
          bottom->visited = true;
          bottom = bottom->to_parent->from;
        }
        while (bottom->to_parent) {
          bottom = bottom->to_parent->from;
          if (bottom->top) ok = false;
        }
        for (auto u : g) ok = ok && (u->visited || !u->top);
      }
    }
    if (ok) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
    // for (auto u : g) {
    //   for (auto e : u->adjusted) {
    //     cout << e->from->id << " " << e->to->id << " " << e->leafs << endl;
    //   }
    // }
  }
}
