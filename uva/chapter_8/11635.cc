#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

// adj[u][?] = (v, x) - edge from u to v of weight x
vll shortest_paths(int from, vector<vector<ii>>& adj) {
  size_t n = adj.size();
  vll distance(n, INF);
  queue<size_t> q;
  vb in_queue(n, false);
  distance[from] = 0;
  q.emplace(from);
  while (!q.empty()) {
    size_t u = q.front(); q.pop(); in_queue[u] = false;
    for (auto e : adj[u]) {
      int v = e.first;
      int d = e.second;
      ll t = distance[u] + d;
      if (t > 600) continue;
      if (t < distance[v]) {
        distance[v] = t;
        if (!in_queue[v]) {
          q.emplace(v);
          in_queue[v] = true;
        }
      }
    }
  }
  return distance;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n;
  while (cin >> n, n) {
    int h; cin >> h;
    vi hotel_indexes(h + 2);
    hotel_indexes[0] = 0;
    for (int i = 1; i <= h; i++) {
      cin >> hotel_indexes[i];
      hotel_indexes[i]--;
    }
    hotel_indexes[h + 1] = n - 1;
    h += 2;
    vector<vector<ii>> roads(n);
    int r; cin >> r;
    for (int i = 0; i < r; i++) {
      int a, b, t;
      cin >> a >> b >> t;
      a--; b--;
      roads[a].emplace_back(b, t);
      roads[b].emplace_back(a, t);
    }

    vvb hotel_connection(h);
    for (auto &v : hotel_connection) v.resize(h);

    for (int i = 0; i < h; i++) {
      auto s = shortest_paths(hotel_indexes[i], roads);
      for (int j = 0; j < h; j++) {
        if (s[hotel_indexes[j]] == INF) continue;
        hotel_connection[i][j] = true;
      }
    }

    vi days_to_hotel(h, INF);
    queue<int> w;
    w.emplace(0);
    days_to_hotel[0] = -1;
    while (!w.empty()) {
      int u = w.front(); w.pop();
      for (int v = 0; v < h; v++) {
        if (!hotel_connection[u][v]) continue;
        if (days_to_hotel[v] != INF) continue;
        days_to_hotel[v] = days_to_hotel[u] + 1;
        w.emplace(v);
      }
    }
    if (days_to_hotel[h - 1] == INF) {
      cout << -1 << endl;
    } else {
      cout << days_to_hotel[h - 1] << endl;
    }
  }
}

