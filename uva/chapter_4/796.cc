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

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

struct node;

using NP = shared_ptr<node>;
using Graph = vector<NP>;

struct node {
  bool visited;
  int index;
  int age;
  int low;
  NP parent;
  Graph adjusted;
};

long t = 0;

void collect(Graph &g, NP x, vector<ii> &links) {
  ++t;
  x->visited = true;
  x->age = x->low = t;
  for (auto y : x->adjusted) {
    if (y->visited) {
      if (y != x->parent) x->low = min(x->low, y->age);
      continue;
    }
    y->parent = x;
    collect(g, y, links);
    x->low = min(x->low, y->low);
    if (y->low > x->age) {
      links.push_back(
        make_pair(min(x->index, y->index),
                  max(x->index, y->index)));
    }
  }
}

int main() {
  int n;
  while (cin >> n) {
    Graph G(n);
    vector<ii> links;
    for (int i = 0; i < n; ++i) {
      G[i] = make_shared<node>();
      G[i]->index = i;
    }
    for (int i = 0; i < n; ++i) {
      int x, k;
      scanf("%d (%d)", &x, &k);
      while (k--) {
        int to;
        scanf("%d", &to);
        G[x]->adjusted.push_back(G[to]);
        G[to]->adjusted.push_back(G[x]);
      }
    }

    for (auto v : G) {
      if (v->visited) continue;
      collect(G, v, links);
    }
    sort(links.begin(), links.end());

    printf("%lu critical links\n", links.size());
    for (auto link : links) {
      printf("%d - %d\n", link.first, link.second);
    }
    printf("\n");
  }
}
