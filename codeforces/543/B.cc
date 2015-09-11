#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using l = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vl = vector<l>;
using vvl = vector<vl>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vvl adj(n);
    for (l i = 0; i < m; i++) {
      l a, b;
      cin >> a >> b; a--; b--;
      adj[a].emplace_back(b);
      adj[b].emplace_back(a);
    }
    vvl distance(n, vl(n, -1));
    for (l i = 0; i < n; i++) {
      queue<l> q;
      q.emplace(i);
      distance[i][i] = 0;
      while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v : adj[u]) {
          if (distance[i][v] != -1) continue;
          distance[i][v] = distance[i][u] + 1;
          q.emplace(v);
        }
      }
    }
    l s0, t0, l0, s1, t1, l1;
    cin >> s0 >> t0 >> l0 >> s1 >> t1 >> l1;
    s0--; t0--; s1--; t1--;
    if (distance[s0][t0] > l0 || distance[s1][t1] > l1) {
      cout << -1 << endl;
    } else {
      l best = max((l)0, m - distance[s0][t0] - distance[s1][t1]);
      for (l i = 0; i < n; i++) {
        for (l j = i + 1; j < n; j++) {
          l t = distance[i][j];
          for (l k = 0; k < 4; k++) {
            l a0 = (k % 2 == 0 ? i : j);
            l b0 = (k % 2 == 0 ? j : i);
            l a1 = (k / 2 == 0 ? i : j);
            l b1 = (k / 2 == 0 ? j : i);
            if (distance[s0][a0] + t + distance[b0][t0] > l0) continue;
            if (distance[s1][a1] + t + distance[b1][t1] > l1) continue;
            best = max(best, m - distance[s0][a0] - distance[s1][a1]
              - distance[b0][t0] - distance[b1][t1] - t);
          }
        }
      }
      cout << best << endl;
    }
  }
}
