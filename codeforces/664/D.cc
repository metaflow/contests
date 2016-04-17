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

struct node;

using pnode = shared_ptr<node>;
using graph = vector<pnode>;

l T = 0;

struct node {
  l state = 0;
  l time = 0;
  l id;
  vector<pnode> adjusted;
  vector<bool> edge_color;
};

vl fill(pnode change, bool color, graph& g, bool& bad) {
  T++;
  vl result;
  if (change->state != 0) {
    bad = true;
    return result;
  }
  change->time = T;
  change->state = 1;
  queue<pnode> q;
  q.emplace(change);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (l i = 0; i < l(u->adjusted.size()); i++) {
      auto v = u->adjusted[i];
      auto c = u->edge_color[i];
      l t = u->state;
      if (c != color) t = -t;
      if (v->state == 0) {
        v->state = t;
        v->time = T;
        q.emplace(v);
        continue;
      }
      if (v->state != t) {
        bad = true;
        return result;
      }
    }
  }
  for (auto u : g) {
    if (u->time == T && u->state == 1) result.emplace_back(u->id);
  }
  return result;
}

void clean(graph& g) {
  for (auto u : g) if (u->time == T) u->state = 0;
}

vl try_color(graph& g, bool color) {
  vl result;
  for (auto& u : g) u->state = 0;
  for (auto u : g) {
    if (u->state != 0) continue;
    for (l i = 0; i < l(u->adjusted.size()); i++) {
      if (u->edge_color[i] == color) continue;

      bool bad = false;
      auto self = fill(u, color, g, bad);
      clean(g);
      if (bad) while (self.size() <= g.size()) self.emplace_back(0);

      bad = false;
      auto other = fill(u->adjusted[i], color, g, bad);
      if (bad) while (other.size() <= g.size()) other.emplace_back(0);

      if (self.size() >= other.size()) {
        swap(self, other);
      } else {
        clean(g);
        fill(u, color, g, bad);
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
    for (l i = 0; i < n; i++) {
      g[i] = make_shared<node>();
      g[i]->id = i;
    }
    for (l i = 0; i < m; i++) {
      l a, b; char c;
      cin >> a >> b >> c; a--; b--;
      bool color = c == 'R';
      g[a]->adjusted.emplace_back(g[b]);
      g[a]->edge_color.emplace_back(color);
      g[b]->adjusted.emplace_back(g[a]);
      g[b]->edge_color.emplace_back(color);
    }
    auto red = try_color(g, true);
    auto blue = try_color(g, false);
    if (red.size() > blue.size()) swap(red, blue);
    if (l(red.size()) > n) {
      cout << "-1" << endl;
    } else {
      cout << red.size() << endl;
      if (red.size()) {
        for (l i = 0; i < l(red.size()); i++) {
          if (i) cout << " ";
          cout << (red[i] + 1);
        }
        cout << endl;
      }

    }
  }
}
