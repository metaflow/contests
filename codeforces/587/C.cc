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

vl top10(vl& a, vl& b) {
  vl c(a);
  c.insert(c.end(), b.begin(), b.end());
  sort(c.begin(), c.end());
  if (c.size() > 10) c.resize(10);
  return c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, q;
  while (cin >> n >> m >> q) {
    vvl adj(n);
    vvl c(n);
    for (l i = 0; i < n - 1; i++) {
      l u, v; cin >> u >> v; u--; v--;
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
    }
    for (l i = 0; i < m; i++) {
      l a; cin >> a; a--;
      c[a].emplace_back(i + 1);
    }
    vvl p(n);
    vector<vvl> t(n);
    queue<l> q;
    p[0].emplace_back(-1);
    q.emplace(0);
    while (!q.empty()) {
      l u = q.front(); q.pop();
      t[u].emplace_back(c[u]);
      if (p[u][0] != -1) t[u][0] = top10(t[u][0], c[p[u][0]]);
      l j = 0;
      while (p[u].back() != -1) {
        j++;
        l w = p[u][j - 1];
        if (p[w].size() + 1 <= j) {
          p[u].emplace_back(-1);
          t[u].emplace_back(top10(t[u][j - 1], t[w].back()));
        } else {
          p[u].emplace_back(p[w][j - 1]);
          t[u].emplace_back(top10(t[u][j - 1], t[w][j - 1]));
        }
      }

      for (auto k : adj[u]) {
        if (!p[k].empty()) continue;
        p[k].emplace_back(u);
        q.emplace(k);
      }
    }
    for (l i = 0; i < n; i++) {
      cerr << i << ":" << endl;
      for (auto j : p[i]) cerr << j << ' ';
      cerr << endl;
      for (auto v : t[i]) {
        cerr << "(";
        for (auto j : v) cerr << j << ", ";
        cerr << "), ";
      }
      cerr << endl;
    }
  }
}
