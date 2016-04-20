#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

l T = 0;

struct node {
  l state = 0;
  l time = 0;
  vector<size_t> adjusted;
  vector<bool> edge_color;
};

using graph = vector<node>;

vl fill(size_t change, bool color, graph& g, bool& bad, vl& affected) {
  T++;
  vl result;
  if (g[change].state != 0) {
    bad = true;
    return result;
  }
  affected.emplace_back(change);
  g[change].time = T;
  g[change].state = 1;
  queue<size_t> q;
  q.emplace(change);
  while (!q.empty()) {
    auto& u = g[q.front()]; q.pop();
    l size = u.adjusted.size();
    for (l i = 0; i < size; i++) {
      auto v = u.adjusted[i];
      auto c = u.edge_color[i];
      l t = u.state;
      if (c != color) t = -t;
      if (g[v].state == 0) {
        affected.emplace_back(v);
        g[v].state = t;
        g[v].time = T;
        q.emplace(v);
        continue;
      }
      if (g[v].state != t) {
        bad = true;
        return result;
      }
    }
  }
  for (auto j : affected) if (g[j].state == 1) result.emplace_back(j);
  return result;
}

vl try_color(graph& g, bool color) {
  vl result;
  for (auto& u : g) u.state = 0;
  auto n = g.size();
  for (size_t u = 0; u < n; u++) {
    if (g[u].state != 0) continue;
    l size = g[u].adjusted.size();
    for (l i = 0; i < size; i++) {
      if (g[u].edge_color[i] == color) continue;
      bool bad = false;
      vl affected;
      auto self = fill(u, color, g, bad, affected);
      for (auto j : affected) g[j].state = 0;
      if (bad) while (self.size() <= g.size()) self.emplace_back(0);
      affected.clear();
      bad = false;
      auto other = fill(g[u].adjusted[i], color, g, bad, affected);
      if (bad) while (other.size() <= g.size()) other.emplace_back(0);

      if (self.size() >= other.size()) {
        swap(self, other);
      } else {
        for (auto j : affected) g[j].state = 0;
        fill(u, color, g, bad, affected);
      }

      for (auto i : self) {
        result.emplace_back(i);
      }
      if (result.size() > g.size()) return result;
      break;
    }
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    graph g(n);
    for (l i = 0; i < m; i++) {
      l a, b; char c;
      cin >> a >> b >> c; a--; b--;
      bool color = c == 'R';
      g[a].adjusted.emplace_back(b);
      g[a].edge_color.emplace_back(color);
      g[b].adjusted.emplace_back(a);
      g[b].edge_color.emplace_back(color);
    }
    auto red = try_color(g, true);
    auto blue = try_color(g, false);
    if (red.size() > blue.size()) swap(red, blue);
    if (l(red.size()) > n) {
      cout << "-1" << endl;
    } else {
      cout << red.size() << endl;
      for (l i = 0; i < l(red.size()); i++) {
        if (i) cout << " ";
        cout << (red[i] + 1);
      }
      cout << endl;
    }
  }
}
