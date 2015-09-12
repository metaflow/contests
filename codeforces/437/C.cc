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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m;
  while (cin >> n >> m) {
    vector<pair<ll, ll>> v(n);
    for (ll i = 0; i < n; i++) {
      cin >> v[i].first;
      v[i].second = i;
    }
    sort(v.begin(), v.end());
    vll ri(n);
    for (ll i = 0; i < n; i++) ri[v[i].second] = i;
    vvll adj(n);
    for (ll i = 0; i < m; i++) {
      ll a, b; cin >> a >> b;
      a = ri[a - 1];
      b = ri[b - 1];
      adj[a].emplace_back(b);
      adj[b].emplace_back(a);
    }
    vb visited(n);
    ll answer = 0;
    for (ll i = 0; i < n; i++) {
      for (auto j : adj[i]) if (j > i) answer += v[i].first;
    }
    cout << answer << endl;
  }
}
