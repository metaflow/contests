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

const int MAX = 16;
ll D[MAX][MAX];
ll DP[1 << 15];

ll dp(ll mask, vi& indexes) {
  if (mask == 0) return 0;
  ll &r = DP[mask];
  if (r == -1) {
    int a = 0;
    r = INF;
    while ((mask & (1 << a)) == 0) a++;
    for (ll b = a + 1; b < MAX; b++) {
      if ((mask & (1 << b)) == 0) continue;
      r = min(r, D[indexes[a]][indexes[b]] +
                 dp((mask ^ (1 << a)) ^ (1 << b), indexes));
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n, n) {
    ll m; cin >> m;
    fill(&D[0][0], &D[MAX][0], INF);
    vi degree(n);
    ll answer = 0;
    for (ll i = 0; i < m; i++) {
      ll u, v, t; cin >> u >> v >> t;
      u--; v--;
      D[u][v] = D[v][u] = min(t, D[u][v]);
      answer += t;
      degree[u]++; degree[v]++;
    }
    vi odd;
    for (ll i = 0; i < n; i++) if (degree[i] % 2 == 1) odd.emplace_back(i);
    ll mask = (1 << odd.size()) - 1;
    fill_n(DP, 1 << 15, -1);
    for (ll k = 0; k < n; k++)
    for (ll i = 0; i < n; i++)
    for (ll j = 0; j < n; j++) D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
    answer += dp(mask, odd);
    cout << answer << endl;
  }
}
