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
using iii = tuple<int,int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = 2000000;

const int MAX_NODES = 10000;
int w_start[MAX_NODES], w_finish[MAX_NODES];

void dijkstra(int start, int (&w)[MAX_NODES], vector<vector<ii>> &edges) {
  priority_queue<ii, vector<ii>, greater<ii>> pq;
  fill(&w[0], &w[MAX_NODES], INF);
  w[start] = 0;
  pq.push(ii(0, start));
  while (!pq.empty()) {
    int uw = get<0>(pq.top());
    int u = get<1>(pq.top());
    pq.pop();
    if (w[u] != uw) continue;
    for (auto e : edges[u]) {
      int v = get<0>(e);
      int ew = get<1>(e);
      int x = w[u] + ew;
      if (w[v] <= x) continue;
      w[v] = x;
      pq.push(ii(w[v], v));
    }
  }
}

int main() {
  int tcc, n, m, s, t, p;
  cin >> tcc;
  while (tcc--) {

    cin >> n >> m >> s >> t >> p;
    --s;
    --t;
    vector<vector<ii>> edges(n);
    vector<vector<ii>> back_edges(n);
    while (m--) {
      int u, v, c;
      cin >> u >> v >> c;
      --u;
      --v;
      edges[u].push_back(ii(v, c));
      back_edges[v].push_back(ii(u, c));
    }
    dijkstra(s, w_start, edges);
    dijkstra(t, w_finish, back_edges);
    int best = -1;
    for (int u = 0; u < n; ++u) {
      for (auto e : edges[u]) {
        if (w_start[u] + e.second + w_finish[e.first] > p) continue;
        best = max(best, e.second);
      }
    }
    cout << best << endl;
  }
}

