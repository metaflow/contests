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
  vl c;
  auto ia = a.begin();
  auto ib = b.begin();
  while ((c.size() < 10) &&
         ((ia != a.end()) || (ib != b.end()))) {
    bool pick_a = true;
    if (ia == a.end() || ib == b.end()) {
      pick_a = (ib == b.end());
    } else {
      pick_a = ((*ia) < (*ib));
    }
    if (pick_a) {
      if (c.empty() || (*ia) != c.back()) c.emplace_back(*ia);
      ++ia;
    } else {
      if (c.empty() || (*ib) != c.back()) c.emplace_back(*ib);
      ++ib;
    }
  }
  return c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, Q;
  while (cin >> n >> m >> Q) {
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
    for (l i = 0; i < n; i++) sort(c[i].begin(), c[i].end());
    vvl p(n);
    vector<vvl> t(n);
    vl depth(n);
    queue<l> q;
    p[0].emplace_back(-1);
    q.emplace(0);
    depth[0] = 0;
    while (!q.empty()) {
      l u = q.front(); q.pop();
      t[u].emplace_back(c[u]);
      if (p[u][0] != -1) t[u][0] = top10(t[u][0], c[p[u][0]]);
      l j = 0;
      while (p[u][j] != -1) {
        l w = p[u][j];
        if (p[w].size() <= j) {
          p[u].emplace_back(-1);
          t[u].emplace_back(top10(t[u][j], t[w].back()));
        } else {
          p[u].emplace_back(p[w][j]);
          t[u].emplace_back(top10(t[u][j], t[w][j]));
        }
        j++;
      }

      for (auto k : adj[u]) {
        if (!p[k].empty()) continue;
        p[k].emplace_back(u);
        depth[k] = depth[u] + 1;
        q.emplace(k);
      }
    }

    // for (l i = 0; i < n; i++) {
    //   cerr << i + 1 << ":" << endl;
    //   for (auto j : p[i]) cerr << j + 1 << ' ';
    //   cerr << endl;
    //   for (auto v : t[i]) {
    //     cerr << "(";
    //     for (auto j : v) cerr << j << ", ";
    //     cerr << "), ";
    //   }
    //   cerr << endl;;
    // }
    for (l i = 0; i < Q; i++) {
      l v, u, a; cin >> v >> u >> a; u--; v--;
      // cerr << u << " " << v << endl;
      vl answer = top10(c[u], c[v]);
      // for (auto i : answer) cerr << i << ' '; cerr << endl;
      if (depth[u] > depth[v]) swap(u, v);
      l j = 100;
      while (depth[v] > depth[u]) {
        while (p[v].size() <= j || p[v][j] == -1 || depth[p[v][j]] < depth[u]) j--;
        answer = top10(answer, t[v][j]);
        v = p[v][j];
      }
      j = 100;
      while (v != u) {
        while (j > 0 && (p[v].size() <= j || p[v][j] == p[u][j])) j--;
        answer = top10(answer, t[v][j]);
        answer = top10(answer, t[u][j]);
        u = p[u][j];
        v = p[v][j];
      }
      l k = min(a, l(answer.size()));
      cout << k;
      // for (auto i : answer) cerr << i << ' '; cerr << endl;
      for (l j = 0; j < k; j++) cout << " " << answer[j];
      cout << endl;
    }
  }
}
