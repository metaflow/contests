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
vll shortest_paths(vll from, vector<vector<ii>>& adj) {
  size_t n = adj.size();
  vll distance(n, INF);
  queue<size_t> q;
  vb in_queue(n, false);
  for (auto u : from) {
    distance[u] = 0;
    q.emplace(u);
    in_queue[u] = true;
  }
  while (!q.empty()) {
    size_t u = q.front(); q.pop(); in_queue[u] = false;
    for (auto e : adj[u]) {
      int v = e.first;
      int d = e.second;
      ll t = distance[u] + d;
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
  ll n, m;
  cin >> n >> m;
  vector<vector<ii>> adj(n);
  while (m--) {
    ll u, v, w;
    cin >> u >> v >> w;
    u--; v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  ll s; cin >> s;
  vll special(s);
  for (ll i = 0; i < s; i++) {
    cin >> special[i];
    special[i]--;
  }
  auto a = shortest_paths(special, adj);
  for (auto i : a) cout << i << endl;
}
