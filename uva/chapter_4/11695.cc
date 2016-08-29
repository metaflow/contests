#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct node;
struct edge;

using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  int i;
  bool visited;
  vector<pedge> edges;
  pedge back;
};

struct edge {
  pnode from, to;
  bool enabled;
  pedge opp;
};

pedge link(pnode a, pnode b) {
  auto ea = make_shared<edge>();
  auto eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->enabled = true; ea->opp = eb;
  a->edges.push_back(ea);
  eb->from = b; eb->to = a; eb->enabled = true; eb->opp = ea;
  b->edges.push_back(eb);
  return ea;
}

graph g;

pnode find_opposite(pnode start) {
  for (auto u : g) {
    u->visited = false;
    u->back.reset();
  }
  queue<pnode> q;
  start->visited = true;
  q.push(start);
  pnode u;
  while (!q.empty()) {
    u = q.front(); q.pop();
    for (auto e : u->edges) {
      if (!e->enabled) continue;
      auto v = e->to;
      if (v->visited) continue;
      v->visited = true;
      v->back = e;
      q.push(v);
    }
  }
  return u;
}

vector<pedge> get_diameter(pnode start) {
  auto t = find_opposite(find_opposite(start));
  vector<pedge> diameter;
  while (t->back) {
    diameter.push_back(t->back);
    t = t->back->from;
  }
  return diameter;
}

pnode find_center(pnode start, int &u) {
  auto d = get_diameter(start);
  u = d.size();
  if (u == 0) return start;
  return d[u / 2]->to;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n;
    cin >> n;
    g.clear();
    g.resize(n);
    for (int i = 0; i < n; ++i) {
      g[i] = make_shared<node>();
      g[i]->i = i + 1;
    }
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      link(g[a], g[b]);
    }

    vector<pedge> diameter = get_diameter(g[0]);

    pedge cut, en;
    int best = INF;
    for (auto e : diameter) {
      e->enabled = false; e->opp->enabled = false;

      int x;
      auto cu = find_center(e->from, x);
      if (x >= best) {
        e->enabled = true; e->opp->enabled = true;
        continue;
      }
      auto cv = find_center(e->to, x);

      if (x >= best) {
        e->enabled = true; e->opp->enabled = true;
        continue;
      }

      auto t = link(cu, cv);
      int d = get_diameter(g[0]).size();
      if (best > d) {
        cut = e;
        en = t;
        best = d;
      }
      t->enabled = false; t->opp->enabled = false;
      e->enabled = true; e->opp->enabled = true;
    }

    printf("%d\n", best);
    printf("%d %d\n", cut->from->i, cut->to->i);
    printf("%d %d\n", en->from->i, en->to->i);
  }
}

