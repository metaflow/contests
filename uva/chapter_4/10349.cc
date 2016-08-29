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
  int flow;
  pedge opposite;
};

struct node {
  vector<pedge> edges;
  pedge back;
  bool visited;
};

const int MAX = 50;

pnode m[MAX][MAX];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void connect(pnode &a, pnode &b, int w) {
  auto ea = make_shared<edge>();
  auto eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->flow = w; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->flow = 0; eb->opposite = ea;
  a->edges.emplace_back(ea);
  b->edges.emplace_back(eb);
}

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->flow));
  e->flow -= d;
  e->opposite->flow += d;
  return d;
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink) {
  int r = 0;
  while (true) {
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!(q.empty() || sink->visited)) {
      auto u = q.front(); q.pop();
      for (auto e : u->edges) {
        auto v = e->to;
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
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int h, w;
    cin >> h >> w;
    vector<pnode> g;
    pnode source = make_shared<node>();
    g.emplace_back(source);
    pnode sink = make_shared<node>();
    g.emplace_back(sink);
    for (auto i = 0; i < h; i++) {
      string s;
      cin >> s;
      for (auto j = 0; j < w; j++) {
        if (s[j] == '*') {
          m[i][j] = make_shared<node>();
          g.emplace_back(m[i][j]);
        } else {
          m[i][j] = nullptr;
        }
      }
    }
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (!m[i][j]) continue;
        if ((i + j) % 2) {
          connect(m[i][j], sink, 1);
        } else {
          connect(source, m[i][j], 1);
          for (int k = 0; k < 4; k++) {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x < 0 || x >= h || y < 0 || y >= w) continue;
            if (!m[x][y]) continue;
            connect(m[i][j], m[x][y], 1);
          }
        }
      }
    }
    cout << (g.size() - 2 -  max_flow(g, source, sink)) << endl;
  }
}
