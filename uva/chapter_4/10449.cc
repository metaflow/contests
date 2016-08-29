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
using graph = vector<pnode>;

struct node {
  int busyness;
  bool in_queue;
  int min = INF;
  int cycle_counter;
  graph adjusted;
};

void walk(pnode start) {
  queue<pnode> q;
  start->min = 0;
  q.push(start); start->in_queue = true; start->cycle_counter--;
  while (!q.empty()) {
    auto u = q.front();
    q.pop(); u->in_queue = false;
    for (auto v : u->adjusted) {
      int w = pow(v->busyness - u->busyness, 3);
      if (v->min <= u->min + w) continue;
      v->min = u->min + w;
      if (v->in_queue) continue;
      q.push(v); v->in_queue = true; v->cycle_counter--;
      if (v->cycle_counter < 0) return; // negative cycle
    }
  }
}

int main() {
  int n;
  int tcc = 0;
  while (cin >> n) {
    ++tcc;
    graph g(n);
    for (int i = 0; i < n; ++i) {
      g[i] = make_shared<node>();
      cin >> g[i]->busyness;
      g[i]->cycle_counter = 2*n;
    }
    int m;
    cin >> m;
    while (m--) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      if (u >= n || v >= n) continue;
      g[u]->adjusted.push_back(g[v]);
    }
    if (n > 0) walk(g[0]);
    int q;
    cin >> q;
    printf("Set #%d\n", tcc);
    while (q--) {
      int x;
      cin >> x;
      --x;
      if (x >= n || g[x]->min < 3 || g[x]->cycle_counter <= n || g[x]->min == INF) {
        printf("?\n");
      } else {
        printf("%d\n", g[x]->min);
      }
    }
  }
}
