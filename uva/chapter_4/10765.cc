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
using ii = pair<int, int>;
using pnode = shared_ptr<node>;
using Graph = vector<pnode>;

int t = 0;

struct node {
  pnode parent;
  int split;
  bool visited;
  int bucket;
  int age, low;
  Graph adjusted;
};

void dfs(pnode &u) {
  u->visited = true;
  ++t;
  u->age = u->low = t;
  // if root is alone then component count will decrease
  if (!u->parent) u->split = -1;
  for (auto v : u->adjusted) {
    if (v->visited) {
      if (v != u->parent) u->low = min(u->low, v->age);
      continue;
    }
    v->parent = u;
    dfs(v);
    u->low = min(u->low, v->low);
    if (u->parent) {
      if (v->low >= u->age) u->split++;
    } else {
      u->split++;
    }
  }
}

int main() {
  int m, n;
  while (cin >> n >> m, n) {
    Graph g(n);

    for (int i = 0; i < n; ++i) g[i] = make_shared<node>();

    int a, b;
    while (cin >> a >> b, a != -1) {
      g[a]->adjusted.push_back(g[b]);
      g[b]->adjusted.push_back(g[a]);
    }

    vector<ii> result;

    int components = 0;

    for (auto x : g) {
      if (x->visited) continue;
      ++components;
      dfs(x);
    }

    for (int i = 0; i < g.size(); ++i) {
      result.push_back(make_pair(i, g[i]->split + components));
    }

    sort(result.begin(), result.end(),
      [](const ii &a, const ii &b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
      });
    for (int i = 0; i < m; ++i) {
      printf("%d %d\n", result[i].first, result[i].second);
    }
    printf("\n");
  }
}
