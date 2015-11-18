#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using ll = pair<l, l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

l try_assign(vl& cities, vvll& roads, l start, l value) {
  for (auto &c : cities) if (c < 2) c = -1;
  queue<l> q;
  q.emplace(start);
  cities[start] = value;
  l assigned = value & 1;
  while (!q.empty()) {
    l u = q.front(); q.pop();
    for (auto p : roads[u]) {
      l v = p.first;
      l e = cities[u] ^ p.second;
      if (cities[v] == -1) {
        assigned += (e & 1);
        cities[v] = e;
        q.emplace(v);
        continue;
      }
      if (cities[v] != e) return INF;
    }
  }
  return assigned;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    // states (-1 unknown, 0 / 1 - selected or not, 2 explored)
    vl cities(n);
    vvll roads(n); // (to, asphalted)
    for (l i = 0; i < m; i++) {
      l u, v, t; cin >> u >> v >> t; u--; v--;
      t = 1 - t;
      roads[u].emplace_back(v, t);
      roads[v].emplace_back(u, t);
    }
    l answer = 0;
    for (l i = 0; i < n; i++) {
      if (cities[i] >= 2) continue;
      l best = INF;
      l best_s = -1;
      for (l s = 0; s < 2; s++) {
        l t = try_assign(cities, roads, i, s);
        if (t < best) {
          best = t;
          best_s = s;
        }
      }
      if (best_s == -1) {
        answer = INF;
        break;
      }
      try_assign(cities, roads, i, best_s + 2);
      answer += best;
    }
    if (answer == INF) {
      cout << "Impossible" << endl;
    } else {
      cout << answer << endl;
      bool first = true;
      for (l i = 0; i < n; i++) {
        if ((cities[i] & 1) == 0) continue;
        if (!first) cout << " "; first = false;
        cout << (i + 1);
      }
      cout << endl;
    }
  }
}
