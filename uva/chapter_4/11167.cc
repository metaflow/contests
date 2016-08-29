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
  int time_start, time_end, t;
  vector<pedge> edges;
  pedge back;
};

struct edge {
  int w;
  pedge opp;
  pnode from, to;
};

void connect(pnode a, pnode b, int w) {
  auto ea = make_shared<edge>();
  auto eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->opp = eb; ea->w = w;
  eb->from = b; eb->to = a; eb->opp = ea; eb->w = 0;
  a->edges.emplace_back(ea);
  b->edges.emplace_back(eb);
}

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->w));
  e->w -= d;
  e->opp->w += d;
  return d;
}

int max_flow(pnode source, pnode sink, graph &g) {
  int a = 0;
  while (true) {
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!(q.empty() || sink->visited)) {
      auto u = q.front(); q.pop();
      for (auto e : u->edges) {
        auto v = e->to;
        if (e->w == 0 || v->visited) continue;
        v->visited = true;
        v->back = e;
        q.push(v);
      }
    }
    if (!sink->visited) break;
    a += adjust(sink->back, INF);
  }
  return a;
}

int main() {
  int n, m, i, j, tc, sum, a, b, v;
  tc = 0;
  while (cin >> n, n) {
    cin >> m;
    tc++;
    graph g;
    auto source = make_shared<node>(); g.emplace_back(source);
    source->time_start = -2;
    auto sink = make_shared<node>(); g.emplace_back(sink);
    sink->time_start = -2;
    vector<tuple<int, pnode, bool>> events;
    sum = 0;
    for (i = 0; i < n; i++) {
      cin >> v >> a >> b;
      sum += v;
      auto u = make_shared<node>(); g.emplace_back(u);
      connect(source, u, v);
      u->time_start = -1;
      events.emplace_back(a, u, true);
      events.emplace_back(b, u, false);
    }
    sort(events.begin(), events.end());

    auto it = events.begin();
    set<pnode> active;
    int start = -1;
    while (it != events.end()) {
      start = get<0>(*it);
      auto next = it;
      while (next != events.end() && get<0>(*next) == start) {
        it = next;
        if (get<2>(*it)) {
          active.insert(get<1>(*it));
        } else {
          active.erase(get<1>(*it));
        }
        next++;
      }
      if (next == events.end()) break;
      int end = get<0>(*next);
      auto u = make_shared<node>(); g.emplace_back(u);
      u->time_start = start;
      u->time_end = end;
      u->t = start;
      int w = end - start;
      connect(u, sink, w * m);
      for (auto v : active) {
        connect(v, u, w);
      }
      it = next;
    }

    printf("Case %d: ", tc);
    if (max_flow(source, sink, g) == sum) {
      printf("Yes\n");
      for (auto u : g) {
        if (u->time_start != -1) continue;
        vector<ii> raw;
        for (auto e : u->edges) {
          if (e->to->time_start < 0 || e->opp->w == 0) continue;
          auto v = e->to;
          int y = v->t + e->opp->w;
          if (y > v->time_end) {
            raw.emplace_back(v->t, v->time_end);
            v->t = v->time_start;
            y -= (v->time_end - v->time_start);
          }
          raw.emplace_back(v->t, y);
          v->t = y;
          if (v->t == v->time_end) v->t = v->time_start;
        }
        sort(raw.begin(), raw.end());
        vector<ii> answer;
        auto i = raw.begin();
        while (i != raw.end()) {
          int a = i->first;
          auto j = i + 1;
          while (j != raw.end() && j->first == i->second) {
            i = j;
            j++;
          }
          answer.emplace_back(a, i->second);
          i++;
        }
        printf("%lu", answer.size());
        for (auto k : answer) printf(" (%d,%d)", k.first, k.second);
        printf("\n");
      }
    } else {
      printf("No\n");
    }
  }
}

