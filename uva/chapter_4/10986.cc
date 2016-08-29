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

struct node;
using pnode = shared_ptr<node>;
using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
using edge = pair<pnode, int>;
const int INF = numeric_limits<int>::max();

struct node {
  int w = INF;
  vector<edge> edges;
};

void dijkstra(pnode u) {
  auto cmp = [](const edge &a, const edge &b) {
    return a.second > b.second;
  };
  priority_queue<edge, vector<edge>, decltype(cmp)> pq(cmp);
  pq.push(make_pair(u, 0));
  while (!pq.empty()) {
    auto x = pq.top().first;
    auto d = pq.top().second;
    pq.pop();
    if (x->w < d) continue;
    for (auto e : x->edges) {
      auto v = e.first;
      if (v->w <= x->w + e.second) continue;
      v->w = x->w + e.second;
      pq.push(make_pair(v, v->w));
    }
  }
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    vector<pnode> g(n);
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
    while (m--) {
      int a, b, w;
      cin >> a >> b >> w;
      g[a]->edges.push_back(make_pair(g[b], w));
      g[b]->edges.push_back(make_pair(g[a], w));
    }
    g[s]->w = 0;
    dijkstra(g[s]);
    printf("Case #%d: ", tc);
    if (g[e]->w == INF) {
      printf("unreachable\n");
    } else {
      printf("%d\n", g[e]->w);
    }
  }
}
