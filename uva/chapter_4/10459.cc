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
  int index;
  int level;
  vector<pnode> adjusted;
  pnode back;
};

graph last_gen(graph &g, pnode &start) {
  for (auto u : g) {
    u->level = 0;
    u->back = nullptr;
  }
  queue<pnode> q;
  graph r;
  start->level = 1;
  q.push(start);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    if (!r.empty() && r.back()->level < u->level) r.clear();
    r.push_back(u);
    for (auto v : u->adjusted) {
      if (v->level) continue;
      v->level = u->level + 1;
      v->back = u;
      q.push(v);
    }
  }
  return r;
}

graph path(pnode u) {
  graph r;
  while (u) {
    r.emplace_back(u);
    u = u->back;
  }
  return r;
}

auto cmp = [](const pnode &a, const pnode &b) {
  return a->index < b->index;
};

int main() {
  int i, j, k, n, a;
  while (cin >> n) {
    graph g(n);
    for (auto &u : g) u = make_shared<node>();
    for (i = 0; i < n; i++) {
      g[i]->index = i + 1;
      cin >> k;
      for (j = 0; j < k; j++) {
        cin >> a;
        a--;
        g[i]->adjusted.push_back(g[a]);
        g[a]->adjusted.push_back(g[i]);
      }
    }
    auto p = path(last_gen(g, last_gen(g, g[0])[0])[0]);
    vector<pnode> best;
    vector<pnode> worst;
    if (p.size() % 2 == 0) {
      best.push_back(p[p.size() / 2]);
      best.push_back(p[p.size() / 2 - 1]);
    } else {
      best.push_back(p[p.size() / 2]);
    }
    printf("Best Roots  :");

    sort(best.begin(), best.end(), cmp);
    for (auto u : best) {
      printf(" %d", u->index);
      auto l = last_gen(g, u);
      worst.insert(worst.end(), l.begin(), l.end());
    }
    sort(worst.begin(), worst.end(), cmp);
    printf("\nWorst Roots :");
    for (auto u : worst) {
      printf(" %d", u->index);
    }
    printf("\n");
  }
}
