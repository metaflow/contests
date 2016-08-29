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

struct edge {
  pnode from, to;
  int capacity;
  pedge opposite;
};

struct node {
  bool visited;
  vector<pedge> edges;
  pedge back;
};



int max_flow(int s, int t, vector<pnode> &g) {
  int mf = 0;
  while (true) {
    int f = 0;

    for (auto u : g) u->visited = false;

    queue<pnode> q;
    q.push(g[s]);
    g[s]->visited = true;

    while(!q.empty()) {
      pnode u = q.front();
      q.pop();
      if (u == g[t]) break;
      for (auto e : u->edges) {
        if (e->capacity <= 0) continue;
        auto v = e->to;
        if (v->visited) continue;
        q.push(v);
        v->visited = true;
        v->back = e;
      }
    }

    if (g[t]->visited) {
      f = INF;
      auto e = g[t]->back;
      while (true) {
        f = min(f, e->capacity);
        if (e->from == g[s]) break;
        e = e->from->back;
      }

      e = g[t]->back;
      while (true) {
        e->capacity -= f;
        e->opposite->capacity += f;
        if (e->from == g[s]) break;
        e = e->from->back;
      }

      mf += f;
    }

    if (f == 0) break;
  }
  return mf;
}

int main() {
  int n;
  int tcc = 0;
  while (cin >> n, n) {
    ++tcc;
    vector<pnode> g(n);
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
    int s, t, m;
    cin >> s >> t >> m;
    --s; --t;
    while (m--) {
      int u, v, w;
      cin >> u >> v >> w;
      --u; --v;
      auto a = make_shared<edge>();
      auto b = make_shared<edge>();
      a->opposite = b;
      b->opposite = a;
      a->capacity = b->capacity = w;
      a->from = b->to = g[u];
      b->from = a->to = g[v];
      g[u]->edges.push_back(a);
      g[v]->edges.push_back(b);
    }
    printf("Network %d\n", tcc);
    printf("The bandwidth is %d.\n\n", max_flow(s, t, g));
  }
}
