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
  bool visited;
  int age, low_link;
  bool in_stack;
  int component;
  Graph edges;
};

int component_count;
int t = 0;
stack<pnode> s;

void mark_components(pnode u) {
  u->visited = true;
  ++t;
  u->age = u->low_link = t;
  s.push(u);
  u->in_stack = true;
  for (auto v : u->edges) {
    if (!v->visited) mark_components(v);
    if (v->in_stack) u->low_link = min(u->low_link, v->low_link);
  }
  if (u->low_link == u->age) {
    while (true) {
      auto v = s.top();
      s.pop();
      v->in_stack = false;
      v->component = component_count;
      if (v == u) break;
    }
    ++component_count;
  }
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
    while (m--) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      g[a]->edges.push_back(g[b]);
    }
    component_count = 0;
    for (int i = 0; i < g.size(); ++i) {
      if (g[i]->visited) continue;
      mark_components(g[i]);
    }
    Graph h(component_count);
    for (int i = 0; i < h.size(); ++i) h[i] = make_shared<node>();
    for (auto u : g) {
      for (auto v : u->edges) {
        if (u->component == v->component) continue;
        h[v->component]->edges.push_back(h[u->component]); // inverted
      }
    }
    int result = 0;
    for (auto u : h) {
      if (u->edges.empty()) ++result;
    }
    printf("%d\n", result);
  }
}
