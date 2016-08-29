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

struct node {
  int w = INF;
  vector<ii> edges;
};

vector<node> g;

void dijkstra(int e) {
  priority_queue<ii, vector<ii>, greater<ii>> pq;
  g[e].w = 0;
  pq.push(make_pair(0, e));
  while (!pq.empty()) {
    int d = pq.top().first;
    node &u = g[pq.top().second];
    pq.pop();
    if (u.w < d) continue;
    for (auto t : u.edges) {
      int w = t.first;
      node &v = g[t.second];
      if (v.w < w + u.w) continue;
      v.w = w + u.w;
      pq.push(make_pair(v.w, t.second));
    }
  }
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n, e, t, m;
    cin >> n >> e >> t >> m;
    --e;
    g.clear();
    g.resize(n);
    while (m--) {
      int a, b, w;
      cin >> a >> b >> w;
      --a;
      --b;
      g[b].edges.push_back(make_pair(w, a));
    }
    dijkstra(e);
    int result = 0;
    for (auto u : g) {
      if (u.w > t) continue;
      ++result;
    }
    cout << result << endl;
    if (tcc) cout << endl;
  }
}
