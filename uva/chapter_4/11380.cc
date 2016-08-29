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

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int x, y, p;

void read_graph(vector<pnode> &g, pnode &source, pnode &sink) {
  int i, j, k; string s;
  vector<vector<int>> ins(x), outs(x);
  g.reserve(x * y * 2);
  for (i = 0; i < x; i++) {
    ins[i].resize(y);
    outs[i].resize(y);
    for (j = 0; j < y; j++) {
      ins[i][j] = g.size(); g.emplace_back(make_shared<node>());
      outs[i][j] = g.size(); g.emplace_back(make_shared<node>());
    }
  }
  for (i = 0; i < x; i++) {
    for (j = 0; j < y; j++) {
      for (k = 0; k < 4; k++) {
        int i2 = i + dx[k]; int j2 = j + dy[k];
        if (i2 < 0 || i2 >= x || j2 < 0 || j2 >= y) continue;
        connect(g[outs[i][j]], g[ins[i2][j2]], INF);
      }
    }
  }
  for (i = 0; i < x; i++) {
    cin >> s;
    for (j = 0; j < y; j++) {
      int w = INF;
      switch (s[j]) {
        case '.': w = 1; break;
        case '*': connect(source, g[ins[i][j]], 1); w = 1; break;
        case '~': w = 0; break;
        case '#': connect(g[outs[i][j]], sink, p); break;
      }
      connect(g[ins[i][j]], g[outs[i][j]], w);
    }
  }
}

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->flow));
  e->flow -= d;
  e->opposite->flow += d;
  return d;
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink) {
  int result = 0;
  while (true) {
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!(q.empty() || sink->visited)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->visited || e->flow == 0) continue;
        v->back = e;
        v->visited = true;
        q.push(v);
      }
    }
    if (!sink->visited) break;
    result += adjust(sink->back, INF);
  }
  return result;
}

int main() {
    while (cin >> x >> y >> p) {
    vector<pnode> g;
    pnode source = make_shared<node>(); g.emplace_back(source);
    pnode sink = make_shared<node>(); g.emplace_back(sink);
    read_graph(g, source, sink);
    cout << max_flow(g, source, sink) << endl;
  }
}

