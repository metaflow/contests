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
  int count;
  vi parent;

  int get_parent(int a) {
    if (parent[a] != a) parent[a] = get_parent(parent[a]);
    return parent[a];
  }
public:
  UnionFind(int size) {
    count = size;
    parent.resize(size);
    for (int i = 0; i < size; ++i) parent[i] = i;
  }

  int sets() {
    return count;
  }

  bool in_set(int a, int b) {
    return get_parent(a) == get_parent(b);
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
    int s, n;
    cin >> s >> n;
    vector<ii> coords(n);
    for (int i = 0; i < n; ++i) cin >> coords[i].first >> coords[i].second;
    vector<tuple<double, int, int>> paths;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        double d = pow(pow(coords[i].first - coords[j].first, 2)
                     + pow(coords[i].second - coords[j].second, 2), 0.5);
        paths.push_back(make_tuple(d, i, j));
      }
    }
    sort(paths.begin(), paths.end());
    int i = 0;
    UnionFind u(n);
    double result = 0;
    while (u.sets() > s) {
      auto p = paths[i++];
      if (u.in_set(get<1>(p), get<2>(p))) continue;
      u.join(get<1>(p), get<2>(p));
      result = get<0>(p);
    }
    printf("%.2f\n", round(result * 100) / 100);
  }
}
