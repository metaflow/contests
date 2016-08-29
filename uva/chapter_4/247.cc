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

using pnode = shared_ptr<node>;
using Graph = vector<pnode>;

struct node {
  string name;
  int age, low_link;
  bool visited, in_stack;
  Graph links;
};

vector<Graph> components;

stack<pnode> s;
int t = 0;

void dfs(pnode u) {
  u->visited = true;
  u->low_link = u->age = ++t;
  s.push(u);
  u->in_stack = true;

  for (auto v : u->links) {
    if (v->visited) {
      if (v->in_stack) u->low_link = min(u->low_link, v->age);
      continue;
    }
    dfs(v);
    u->low_link = min(u->low_link, v->low_link);
  }

  if (u->low_link == u->age) {
    vector<pnode> c;
    while (true) {
      auto v = s.top();
      s.pop();
      v->in_stack = false;
      c.push_back(v);
      if (u == v) break;
    }
    components.push_back(c);
  }
}

int main() {
  int n, m;
  int  tc = 0;
  while (cin >> n >> m, n) {
    ++tc;
    components.clear();
    if (tc != 1) printf("\n");
    map<string, pnode> names;
    for (int i = 0; i < m; ++i) {
      string f, t;
      cin >> f >> t;
      if (!names.count(f)) {
        names[f] = make_shared<node>();
        names[f]->name = f;
      }
      if (!names.count(t)) {
        names[t] = make_shared<node>();
        names[t]->name = t;
      }
      names[f]->links.push_back(names[t]);
    }
    for (auto p : names) {
      if (p.second->visited) continue;
      dfs(p.second);
    }
    printf("Calling circles for data set %d:\n", tc);
    for (auto c : components) {
      cout << c[0]->name;
      for (int i = 1; i < c.size(); ++i) cout << ", " << c[i]->name;
      cout << endl;
    }
  }
}
