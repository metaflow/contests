#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

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

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited = false;
  vector<pedge> adjusted;
  pedge back;
  l id = 0;
  l next_edge = 0;
};

struct edge {
  pnode from, to;
  bool visited = false;
};

pedge connect(pnode &a, pnode &b) {
  pedge e = make_shared<edge>();
  e->from = a; e->to = b;
  a->adjusted.emplace_back(e);
  b->adjusted.emplace_back(e);
  return e;
}

bool loop(vector<pnode>& g) {
  for (auto& x : g) {
    while (x->next_edge < x->adjusted.size()) {
      auto u = x;
      while (u->next_edge < u->adjusted.size()) {
        auto e = u->adjusted[u->next_edge];
        u->next_edge++;
        if (e->visited) continue;
        e->visited = true;
        if (e->from != u) swap(e->from, e->to);
        u = e->to;
        if (u == x) break;
      }
      if (u != x) return false;
    }
  }
  return true;
}

bool connected(vector<pnode>& g) {
  queue<pnode> q;
  q.emplace(g[0]);
  g[0]->visited = true;
  l visited = 1;
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (auto e : u->adjusted) {
      auto v = (e->from == u) ? e->to : e->from;
      if (v->visited) continue;
      v->visited = true;
      visited++;
      q.emplace(v);
    }
  }
  return visited == g.size();
}

bool possible_to_build_eulerian_path(vector<pnode>& g) {
  for (auto u : g) if (u->adjusted.size() % 2) return false;
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vector<pnode> g(n);
    vector<pedge> edges(m);
    for (int i = 0; i < n; i++) {
      g[i] = make_shared<node>();
      g[i]->id = i + 1;
    }
    for (l i = 0; i < m; i++) {
      l a, b; cin >> a >> b; a--; b--;
      edges[i] = connect(g[a], g[b]);
    }
    // check if connected and number of vertices with odd degree
    if (connected(g) && possible_to_build_eulerian_path(g) &&
        loop(g)) {
      cout << "YES" << endl;
      for (const auto e : edges) {
        cout << e->from->id << ' ' << e->to->id << endl;
      }
    } else {
      cout << "NO" << endl;
    }
  }
}
