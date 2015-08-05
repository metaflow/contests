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
  ll age, reachable;
  pnode parent;
  bool visited, in_queue;
  vector<pedge> forward, backward;
  ll ds, dt;
};

struct edge {
  pnode from, to;
  ll w;
  bool candidate = false, bridge = false;
  pedge opposite;
};

pedge connect(pnode &a, pnode &b, ll w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->w = w; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->w = w; eb->opposite = ea;
  a->forward.emplace_back(ea);
  b->backward.emplace_back(eb);
  return ea;
}

void shortest_paths_ff(graph& g, pnode from) {
  for (auto u : g) {
    u->ds = INF;
    u->in_queue = false;
  }
  queue<pnode> q;
  from->ds = 0;
  q.emplace(from);
  while (!q.empty()) {
    auto u = q.front(); q.pop(); u->in_queue = false;
    for (auto e : u->forward) {
      auto v = e->to;
      ll t = u->ds + e->w;
      if (t < v->ds) {
        v->ds = t;
        if (!v->in_queue) {
          q.emplace(v);
          v->in_queue = true;
        }
      }
    }
  }
}

void shortest_paths_bw(graph& g, pnode from) {
  for (auto u : g) {
    u->dt = INF;
    u->in_queue = false;
  }
  queue<pnode> q;
  from->dt = 0;
  q.emplace(from);
  while (!q.empty()) {
    auto u = q.front(); q.pop(); u->in_queue = false;
    for (auto e : u->backward) {
      auto v = e->to;
      ll t = u->dt + e->w;
      if (t < v->dt) {
        v->dt = t;
        if (!v->in_queue) {
          q.emplace(v);
          v->in_queue = true;
        }
      }
    }
  }
}

ll age = 0;

void dfs(pnode u) {
  age++;
  u->age = age;
  u->reachable = age;
  for (auto e : u->forward) {
    if (!e->candidate) continue;
    auto v = e->to;
    if (v->age == 0) {
      v->parent = u;
      dfs(v);
      if (v->reachable > u->age) e->bridge = true;
    }
    if (v != u->parent) u->reachable = min(u->reachable, v->reachable);
  }

  for (auto e : u->backward) {
    if (!e->candidate) continue;
    auto v = e->to;
    if (v->age == 0) {
      v->parent = u;
      dfs(v);
      if (v->reachable > u->age) e->opposite->bridge = true;
    }
    if (v != u->parent) u->reachable = min(u->reachable, v->reachable);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m, s, t;
  while (cin >> n >> m >> s >> t) {
    s--; t--;
    graph g(n);
    for (auto& u : g) {
      u = make_shared<node>();
      u->age = 0;
      u->reachable = 0;
    }
    vector<pedge> edges;
    for (ll i = 0; i < m; i++) {
      ll a, b, w;
      cin >> a >> b >> w; a--; b--;
      edges.emplace_back(connect(g[a], g[b], w));
    }

    shortest_paths_ff(g, g[s]);
    shortest_paths_bw(g, g[t]);
    ll best = g[s]->dt;
    for (auto e : edges) {
      ll d = e->from->ds + e->w + e->to->dt;
      e->candidate = e->opposite->candidate = (d == best);
    }
    dfs(g[s]);


    for (auto e : edges) {
      ll d = e->from->ds + e->w + e->to->dt;
      if (e->bridge) {
        cout << "YES" << endl;
        continue;
      }
      ll repair = d - best + 1;
      if (repair >= e->w) {
        cout << "NO" << endl;
        continue;
      }
      cout << "CAN " << repair << endl;
    }
  }
}
