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

const int MAX = 1001;
ll DP[MAX][2];

ll dp(ll p, ll parent, int force, vvi& adj) {
  ll &r = DP[p][force];
  if (r == -1) {
    r = 1;
    for (auto i : adj[p]) {
      if (i == parent) continue;
      r += dp(i, p, 0, adj);
    }
    if (force != 1) {
      ll t = 0;
      for (auto i : adj[p]) {
        if (i == parent) continue;
        t += dp(i, p, 1, adj);
      }
      r = min(r, t);
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n, n) {
    vvi adj(n);
    for (ll i = 0; i < n; i++) {
      ll k; cin >> k;
      for (ll j = 0; j < k; j++) {
        int a; cin >> a; a--;
        adj[i].emplace_back(a);
      };
    }
    fill(&DP[0][0], &DP[MAX][0], -1);
    ll answer = dp(0, -1, 0, adj);
    if (answer == 0) answer = 1;
    cout << answer << endl;
  }
}
