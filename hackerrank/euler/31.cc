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

vll coins = {1, 2, 5, 10, 20, 50, 100, 200};
const int MAX = 100001;
const ll MOD = 1000000007;
ll dp[MAX][8];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  for (ll i = 0; i < 8; i++) dp[0][i] = 0;
  dp[0][0] = 1;
  for (ll i = 0; i < MAX; i++) {
    for (ll j = 0; j < 8; j++) {
      if (j + 1 < 8) {
        dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD;
      }
      ll w = coins[j] + i;
      if (w < MAX) {
        dp[w][j] = (dp[w][j] + dp[i][j]) % MOD;
      }
    }
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    cout << dp[n][7] << endl;
  }
}
