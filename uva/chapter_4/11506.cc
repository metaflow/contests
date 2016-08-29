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
  bool visited;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  int flow;
  pedge opposite;
};

void connect(pnode &a, pnode &b, int w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->flow = w; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->flow = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->flow));
  e->flow -= d;
  e->opposite->flow += d;
  return d;
}

int max_flow(graph &g, pnode &source, pnode &sink) {
  int r = 0;
  while (true) {
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!(q.empty() || sink->visited)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto &v = e->to;
        if (v->visited || e->flow == 0) continue;
        v->back = e;
        q.push(v); v->visited = true;
      }
    }
    if (!sink->visited) break;
    r += adjust(sink->back, INF);
  }
  return r;
}

int main() {
  int m, w, i, j, k, c;
  while (cin >> m >> w, m) {
    graph g(2 * (m + 1));
    for (auto &u : g) u = make_shared<node>();
    for (i = 2; i < m; i++) {
      cin >> j >> c;
      connect(g[2 * j], g[2 * j + 1], c);
    }
    connect(g[2], g[3], INF);
    connect(g[2*m], g[2*m + 1], INF);
    for (i = 0; i < w; i++) {
      cin >> j >> k >> c;
      connect(g[2*j + 1], g[2*k], c);
      connect(g[2*k + 1], g[2*j], c);
    }
    cout << max_flow(g, g[2], g[2*m + 1]) << endl;
  }
}

