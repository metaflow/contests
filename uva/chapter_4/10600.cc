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

class UnionFind {
  vi parent;
  int count;

  int get_parent(int a) {
    if (a != parent[a]) parent[a] = get_parent(parent[a]);
    return parent[a];
  }
public:
  UnionFind(int n) {
    count = n;
    parent.resize(n);
    for (int i = 0; i < n; ++i) parent[i] = i;
  }

  bool in_set(int a, int b) {
    return get_parent(a) == get_parent(b);
  }

  int sets() {
    return count;
  }

  void join(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a == b) return;
    --count;
    parent[a] = b;
  }
};

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> paths;
    while (m--) {
      int a, b, c;
      cin >> a >> b >> c;
      paths.push_back(make_tuple(c, a - 1, b - 1));
    }
    sort(paths.begin(), paths.end());
    set<int> best_edges;
    UnionFind u(n);
    int first = 0;
    for (int i = 0; i < paths.size() && u.sets() > 1; ++i) {
      auto p = paths[i];
      if (u.in_set(get<1>(p), get<2>(p))) continue;
      u.join(get<1>(p), get<2>(p));
      first += get<0>(p);
      best_edges.insert(i);
    }

    int second = numeric_limits<int>::max();

    for (auto k : best_edges) {
      int t = 0;
      UnionFind v(n);
      for (int i = 0; i < paths.size() && v.sets() > 1; ++i) {
        auto p = paths[i];
        if (v.in_set(get<1>(p), get<2>(p)) || i == k) continue;
        v.join(get<1>(p), get<2>(p));
        t += get<0>(p);
      }
      if (v.sets() == 1) second = min(second, t);
    }
    printf("%d %d\n", first, second);
  }
}
