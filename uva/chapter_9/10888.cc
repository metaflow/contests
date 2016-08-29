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
  ll r, c;
  bool in_queue;
  ll potential;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  ll capacity, original_capacity;
  ll cost, original_cost;
  pedge opposite;

};

void connect(pnode &a, pnode &b, ll w, ll cost) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->capacity = ea->original_capacity = w;
  ea->cost = ea->original_cost = cost; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->capacity = eb->original_capacity = 0;
  eb->cost = eb->original_cost = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

void sssp(pnode start, graph& g) {
  for (auto u : g) {
    u->potential = INF;
    u->in_queue = false;
    u->back = NULL;
  }
  queue<pnode> q;
  start->potential = 0;
  start->in_queue = true;
  q.emplace(start);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    u->in_queue = false;
    for (auto e : u->adjusted) {
      if (e->capacity == 0) continue;
      auto v = e->to;
      ll t = u->potential + e->cost;
      if (t >= v->potential) continue;
      v->potential = t;
      v->back = e;
      if (v->in_queue) continue;
      v->in_queue = true;
      q.emplace(v);
    }
  }
  // update potentials
  for (auto u : g) {
    for (auto e : u->adjusted) {
      if (e->original_capacity == 0) continue;
      e->cost += e->from->potential - e->to->potential;
    }
  }
}

ll min_cost_max_flow(graph& g, pnode s, pnode t) {
  while (true) {
    sssp(s, g);
    if (t->potential == INF) break;
    // augment
    stack<pedge> a;
    ll m = INF;
    auto u = t;
    while (u->back) {
      a.push(u->back);
      m = min(m, u->back->capacity);
      u = u->back->from;
    }
    while (!a.empty()) {
      auto e = a.top(); a.pop();
      e->capacity -= m;
      e->opposite->capacity += m;
    }
  }
  ll cost = 0;
  for (auto u : g) {
    for (auto e : u->adjusted) {
      cost += (e->original_capacity - e->capacity) * e->original_cost;
    }
  }
  return cost;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll h, w;
    cin >> h >> w;
    vector<string> f(h);
    graph g;
    auto s = make_shared<node>(); g.emplace_back(s);
    auto t = make_shared<node>(); g.emplace_back(t);
    graph boxes, places;
    for (ll i = 0; i < h; i++) {
      cin >> f[i];
      for (ll j = 0; j < w; j++) {
        if (f[i][j] == 'B') {
          auto b = make_shared<node>();
          b->r = i; b->c = j;
          boxes.emplace_back(b);
        }
        if (f[i][j] == 'X') {
          auto b = make_shared<node>();
          b->r = i; b->c = j;
          places.emplace_back(b);
        }
      }
    }
    for (auto p : places) {
      g.emplace_back(p);
      connect(p, t, 1, 0);
    }
    for (auto b : boxes) {
      g.emplace_back(b);
      connect(s, b, 1, 0);
      vvll m(h, vll(w, -1));
      queue<ii> q;
      m[b->r][b->c] = 0;
      q.emplace(b->r, b->c);
      const int dx[] = {1, 0, -1, 0};
      const int dy[] = {0, 1, 0, -1};
      while (!q.empty()) {
        ll r = q.front().first, c = q.front().second; q.pop();
        ll d = m[r][c];
        for (int i = 0; i < 4; i++) {
          ll x = r + dx[i], y = c + dy[i];
          if (x < 0 || x >= h || y < 0 || y >= w) continue;
          if (m[x][y] != -1) continue;
          if (f[x][y] == '#') continue;
          m[x][y] = d + 1;
          q.emplace(x, y);
        }
      }
      for (auto p : places) {
        if (m[p->r][p->c] == -1) continue;
        connect(b, p, 1, m[p->r][p->c]);
      }
    }
    cout << min_cost_max_flow(g, s, t) << endl;
  }
}
