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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

bool bipartite_matching_connect(const int u, vvb& m, vi& to, vb& used) {
  for (size_t v = 0; v < to.size(); v++) {
    if (!m[u][v] || used[v]) continue;
    used[v] = true;
    if (to[v] == -1 || bipartite_matching_connect(to[v], m, to, used)) {
      to[v] = u;
      return true;
    }
  }
  return false;
}

// {A} => {B}, m[i][j] == A[i] -> B[j]
int bipartite_matching(vvb& m) {
  if (m.empty()) return 0;
  vi to(m[0].size(), -1);
  int result = 0;
  for (size_t u = 0; u < m.size(); u++) {
    vb used(to.size());
    if (bipartite_matching_connect(u, m, to, used)) result++;
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, m; cin >> n >> m;
    vvb connections(n, vb(n));
    for (ll i = 0; i < m; i++) {
      ll s, e; cin >> s >> e;
      s--; e--;
      connections[s][e] = true;
    }
    ll answer = n - bipartite_matching(connections);
    cout << answer << endl;
  }
}
