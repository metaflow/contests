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

class Uds {
private:
  vi parent;
  int components;

  int get_parent(int i) {
    if (parent[i] == i) return i;
    parent[i] = get_parent(parent[i]);
    return parent[i];
  }
public:
  Uds(int n) {
    parent.resize(n);
    components = n;
    for (int i = 0; i < n; ++i) parent[i] = i;
  }

  bool in_set(int a, int b) {
    return (get_parent(a) == get_parent(b));
  }

  void join(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a == b) return;
    --components;
    parent[a] = b;
  }

  int count() {
    return components;
  }
};

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    int n, threshold;
    cin >> n >> threshold;
    vector<ii> coords;
    for (int i = 0; i < n; ++i) {
      int a, b;
      cin >> a >> b;
      coords.push_back(make_pair(a, b));
    }
    vector<tuple<double, int, int>> paths;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        double d = sqrt(pow(coords[i].first - coords[j].first, 2)
                   + pow(coords[i].second - coords[j].second, 2));
        paths.push_back(make_tuple(d, i, j));
      }
    }
    sort(paths.begin(), paths.end());
    reverse(paths.begin(), paths.end());
    Uds s(n);
    double roads = 0.0;
    double rails = 0.0;
    int states = n;
    while (s.count() != 1) {
      auto p = paths.back();
      paths.pop_back();
      if (s.in_set(get<1>(p), get<2>(p))) continue;
      s.join(get<1>(p), get<2>(p));
      double d = get<0>(p);
      if (d - threshold < 1e-6) {
        roads += d;
        --states;
      } else {
        rails += d;
      }
    }
    printf("Case #%d: %d %.0f %.0f\n", tc, states, round(roads), round(rails));
  }
}
