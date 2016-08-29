#include<bits/stdc++.h>
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
  int age;
  vector<pedge> edges;
  vector<pedge> back;
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
  a->edges.emplace_back(ea);
  b->edges.emplace_back(eb);
}

int adjust(pnode &u, int out) {
  if (u->back.empty()) return out; //source
  int sum = 0;
  for (auto e : u->back) {
    int t = adjust(e->from, min(out - sum, e->flow));
    e->flow -= t;
    e->opposite->flow += t;
    sum += t;
    if (sum == out) break;
  }
  return sum;
}

int max_flow(graph &g, pnode &source, pnode &sink) {
  int r = 0;
  while (true) {
    for (auto u : g) { u->age = INF; u->back.clear(); }
    queue<pnode> q;
    q.push(source); source->age = 0;
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      for (auto e : u->edges) {
        auto v = e->to;
        if (e->flow == 0 || v->age <= u->age) continue;
        v->back.emplace_back(e);
        if (v->age == INF) {
          q.emplace(v);
          v->age = u->age + 1;
        }
      }
    }
    if (sink->age == INF) break;
    r += adjust(sink, INF);
  }
  return r;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int bolts, nuts;
    cin >> bolts >> nuts;
    graph g(bolts + nuts + 2);
    for (auto &u : g) u = make_shared<node>();
    auto &source = g[0];
    auto &sink = g[1];
    for (int i = 0; i < bolts; i++) connect(source, g[i + 2], 1);
    for (int i = 0; i < nuts; i++) connect(g[i + 2 + bolts], sink, 1);
    for (int i = 0; i < bolts; i++) {
      for (int j = 0; j < nuts; j++) {
        int t;
        cin >> t;
        if (t) connect(g[i + 2], g[j + 2 + bolts], 1);
      }
    }
    printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n",
      tc, max_flow(g, source, sink));
  }
}
