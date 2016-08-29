#include <vector>
#include <list>
#include <map>
#include <queue>
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

using pnode = shared_ptr<node>;
using Graph = vector<pnode>;

struct node {
  int day;
  Graph adjusted;
};

int main() {
  int n;
  cin >> n;
  Graph g(n);
  for (int i = 0; i < n; ++i) g[i] = make_shared<node>();
  for (int i = 0; i < n; ++i) {
    int m;
    cin >> m;
    for (int j = 0; j < m; ++j) {
      int x;
      cin >> x;
      g[i]->adjusted.push_back(g[x]);
    }
  }
  int tcc;
  cin >> tcc;

  while (tcc--) {
    int s;
    cin >> s;
    for (auto u : g) {
      u->day = -1;
    }
    g[s]->day = 0;
    int boom = 0;
    int boom_day = 0;
    int b = 0, d = 0;
    queue<pnode> q;
    q.push(g[s]);
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      if (u->day != d) {
        d = u->day;
        b = 0;
      }
      ++b;
      if (b > boom || d == 1) {
        boom = b;
        boom_day = d;
      }
      for (auto v : u->adjusted) {
        if (v->day != -1) continue;
        v->day = d + 1;
        q.push(v);
      }
    }
    if (boom_day == 0) {
      printf("0\n");
    } else {
      printf("%d %d\n", boom, boom_day);
    }
  }
}
