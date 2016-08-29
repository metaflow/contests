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

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
using pnode = shared_ptr<node>;
using Graph = vector<pnode>;

struct node {
  bool visited, active;
  int age, low_link;
  Graph adjusted;
};

stack<pnode> s;
int components_count = 0;
int t = 0;

void dfs(pnode u) {
  u->age = u->low_link = ++t;
  u->visited = u->active = true;
  s.push(u);

  for (auto v : u->adjusted) {
    if (!v->visited) dfs(v);
    if (v->active) u->low_link = min(u->low_link, v->low_link);
  }

  if (u->low_link == u->age) {
    ++components_count;
    while (true) {
      auto v = s.top();
      s.pop();
      v->active = false;
      if (v == u) break;
    }
  }
}

int main() {
  int n, m;
  while (cin >> n >> m, n) {
    Graph g(n);
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
    for (int i = 0; i < m; ++i) {
      int a, b, p;
      cin >> a >> b >> p;
      --a;
      --b;
      g[a]->adjusted.push_back(g[b]);
      if (p == 2) g[b]->adjusted.push_back(g[a]);
    }
    components_count = 0;
    for (auto u : g) {
      if (u->visited) continue;
      dfs(u);
      if (components_count > 1) break;
    }
    int a = 1;
    if (components_count > 1) a = 0;
    cout << a << endl;
  }
}
