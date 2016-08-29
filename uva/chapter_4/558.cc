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

struct node {
  int t = INF;
  int count;
  bool in_queue;
  vector<pair<pnode, int>> edges;
};

bool negative_cycle(pnode start, int n) {
  start->t = 0;
  queue<pnode> q;
  q.push(start);
  start->count++;
  start->in_queue = true;
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    u->in_queue = false;
    for (auto e : u->edges) {
      auto v = e.first;
      int w = e.second;
      if (v->t <= u->t + w) continue;
      v->t = u->t + w;
      if (v->in_queue) continue;
      q.push(v);
      v->count++;
      v->in_queue = true;
      if (v->count >= n) return true;
    }
  }
  return false;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n, m;
    cin >> n >> m;
    vector<pnode> g(n);
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      g[u]->edges.push_back(make_pair(g[v], w));
    }
    if (negative_cycle(g[0], n)) {
      printf("possible\n");
    } else {
      printf("not possible\n");
    }
  }
}
