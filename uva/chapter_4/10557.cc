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
  int e, best_e;
  bool in_queue;
  int cycle_counter;
  graph adjusted;
};

int n;

void walk(pnode start) {
  queue<pnode> q;
  q.push(start); start->in_queue = true; start->cycle_counter--;
  while (!q.empty()) {
    auto u = q.front(); q.pop(); u->in_queue = false;
    for (auto v : u->adjusted) {
      if (u->best_e + v->e <= v->best_e) continue;
      v->best_e = u->best_e + v->e;
      if (v->in_queue) continue;
      q.push(v);
      v->in_queue = true;
      v->cycle_counter--;
      if (v->cycle_counter < n) {
        v->best_e = 100000;
      }
      if (v->cycle_counter < 0) return;
    }
  }
}

int main() {
  while (cin >> n, n != -1) {
    graph g(n);
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
    for (int i = 0; i < n; ++i) {
      g[i]->cycle_counter = 2 * n;
      int m;
      cin >> g[i]->e >> m;
      while (m--) {
        int v;
        cin >> v;
        --v;
        g[i]->adjusted.push_back(g[v]);
      }
    }
    bool winnable = false;
    if (n > 0) {
      g[0]->best_e = 100;
      walk(g[0]);
      winnable = (g[n - 1]->best_e > 0);
    }
    if (winnable) {
      printf("winnable\n");
    } else {
      printf("hopeless\n");
    }
  }
}
