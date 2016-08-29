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
  int set_count;
  int get_parent(int i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
public:
  UnionFind(int n) {
    parent.resize(n);
    set_count = n;
    for (int i = 0; i < n; ++i) parent[i] = i;
  }

  int count() {
    return set_count;
  }

  bool in_set(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    return (a == b);
  }

  void join(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a == b) return;
    parent[a] = b;
    set_count--;
  }
};

int main() {
  int n, m;
  while (cin >> n >> m, n) {
    UnionFind u(n);
    vector<tuple<int, int, int>> paths;
    int sum = 0;
    for (int i = 0; i < m; ++i) {
      int a, b, c;
      cin >> a >> b >> c;
      sum += c;
      paths.push_back(make_tuple(c, a, b));
    }
    sort(paths.begin(), paths.end());
    int j = 0;
    while (u.count() > 1) {
      auto p = paths[j++];
      if (u.in_set(get<1>(p), get<2>(p))) continue;
      u.join(get<1>(p), get<2>(p));
      sum -= get<0>(p);
    }
    cout << sum << endl;
  }
}
