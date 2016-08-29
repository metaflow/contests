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

class UnionFind {
  vector<size_t> parent;
  size_t components;

  size_t get_parent(size_t i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
public:
  UnionFind(size_t size) {
    parent.resize(size);
    components = size;
    for (size_t i = 0; i < size; i++) parent[i] = i;
  }

  bool same_set(size_t i, size_t j) {
    return get_parent(i) == get_parent(j);
  }

  void join(size_t i, size_t j) {
    i = get_parent(i);
    j = get_parent(j);
    if (i == j) return;
    parent[i] = j;
    components--;
  }

  size_t components_count() {
    return components;
  }

  size_t set_id(size_t i) {
    return get_parent(i);
  }
};

int main() {
  int n, r;
  while (cin >> n >> r) {
    vi v(n, 0);
    UnionFind u(n);
    for (int k = 0; k < r; k++) {
      int i, j;
      cin >> i >> j;
      v[i]++; v[j]++;
      u.join(i, j);
    }
    bool odd = false;
    int t = -1;
    for (size_t j = 0; j < n; j++) {
      if (u.set_id(j) == j || u.set_id(j) == t) continue;
      if (t == -1) {
        t = u.set_id(j);
        continue;
      }
      odd = true;
    }
    for (auto i : v) if (i % 2 == 1) odd = true;
    if (r == 0 || odd) {
      printf("Not Possible\n");
    } else {
      printf("Possible\n");
    }
  }
}
