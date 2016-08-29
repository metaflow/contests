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

using pnode = shared_ptr<node>;
using edge = pair<pnode, int>;

struct node {
  int w = INF;
  vector<edge> edges;
};

void dijkstra(pnode start) {
  auto cmp = [](const edge &a, const edge &b) {
    return a.second > b.second;
  };
  priority_queue<edge, vector<edge>, decltype(cmp)> pq(cmp); // not edges but pairs of node / relaxed w
  pq.push(make_pair(start, start->w));

  while (!pq.empty()) {
    auto u = pq.top().first;
    auto d = pq.top().second;
    pq.pop();
    if (u->w < d) continue;
    for (auto e : u->edges) {
      auto v = e.first;
      auto w = e.second;
      if (v->w <= w + u->w) continue;
      v->w = w + u->w;
      pq.push(make_pair(v, v->w));
    }
  }
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    vi t(n);
    vector<pnode> floors(100);
    for (auto &x : floors) x = make_shared<node>();
    for (int i = 0; i < n; ++i) cin >> t[i];
    string s;
    getline(cin, s);
    for (int i = 0; i < n; ++i) {
      getline(cin, s);
      stringstream ss(s);
      vi h;
      pnode p;
      int f;
      while (ss >> f) {
        h.push_back(f);
      }
      vector<pnode> elevator(h.size());
      for (int j = 0; j < h.size(); ++j) {
        elevator[j] = make_shared<node>();
        elevator[j]->edges.push_back(make_pair(floors[h[j]], 0));
        floors[h[j]]->edges.push_back(
          make_pair(elevator[j], h[j] == 0 ? 0 : 60));
        if (j > 0) {
          elevator[j]->edges.push_back(
            make_pair(elevator[j - 1], t[i] * (h[j] - h[j-1])));
          elevator[j - 1]->edges.push_back(
            make_pair(elevator[j], t[i] * (h[j] - h[j-1])));
        }
      }
    }
    floors[0]->w = 0;
    dijkstra(floors[0]);
    if (floors[k]->w == INF) {
      printf("IMPOSSIBLE\n");
    } else {
      printf("%d\n", floors[k]->w);
    }
  }
}
