#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

struct disjoint_set {
  vl parent;
  void check(l i) {
    if (i < parent.size()) return;
    l k = parent.size();
    parent.resize(i + 1);
    for (l j = k; j < parent.size(); j++) parent[j] = j;
  }
  l get_parent(l i) {
    check(i);
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
  bool connected(l i, l j) {
    // cerr << i << " ? " << j << endl;
    return get_parent(i) == get_parent(j);
  }
  void connect(l i, l j) {
    l a = get_parent(i);
    l b = get_parent(j);
    // cerr << a << "+" << b << endl;
    parent[a] = b;
  }
};

l get_index(l i, unordered_map<l, l>& m, l& next) {
  if (!m.count(i)) {
    m[i] = next;
    next += 2;
  }
  return m[i];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    disjoint_set s;
    l next_row = 0;
    l next_column = e6;
    unordered_map<l, l> rows, columns;
    bool possible = true;
    for (l i = 0; i < n; i++) {
      l r, c, v1, v2; cin >> r >> c >> v1 >> v2;
      r = get_index(r, rows, next_row);
      l _r = r + 1;
      c = get_index(c, columns, next_column);
      l _c = c + 1;
      if (v1 == v2) {
        s.connect(r, c);
        s.connect(_r, _c);
      } else {
        s.connect(r, _c);
        s.connect(_r, c);
      }
      possible = possible && (!s.connected(r, _r));
      if (possible) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    }
  }
}
