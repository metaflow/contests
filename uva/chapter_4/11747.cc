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
private:
  vi parent;

  int get_parent(int a) {
    if (parent[a] != a) parent[a] = get_parent(parent[a]);
    return parent[a];
  }

public:
  UnionFind(int size) {
    parent.resize(size);
    for (int i = 0; i < size; ++i) parent[i] = i;
  }

  bool in_set(int a, int b) {
    return get_parent(a) == get_parent(b);
  }

  void join(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a == b) return;
    parent[a] = b;
  }
};

int main() {
  int n, m;
  while (cin >> n >> m, n) {
    vector<tuple<int, int, int>> edges;
    UnionFind u(n);
    for (int i = 0; i < m; ++i) {
      int a, b, w;
      cin >> a >> b >> w;
      edges.push_back(make_tuple(w, a, b));
    }
    sort(edges.begin(), edges.end());
    vi result;
    for (auto e : edges) {
      if (u.in_set(get<1>(e), get<2>(e))) {
        result.push_back(get<0>(e));
      } else {
        u.join(get<1>(e), get<2>(e));
      }
    }
    if (result.empty()) {
      printf("forest\n");
    } else {
      for (int i = 0; i < result.size(); ++i) {
        if (i) printf(" ");
        printf("%d", result[i]);
      }
      printf("\n");
    }
  }
}
