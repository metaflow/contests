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
const int MAX = 4001;
const ll MOD = 1000000007;

ll C[MAX][MAX];
ll S[MAX][MAX];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  C[0][0] = 1;
  for (ll i = 1; i < MAX; i++) {
    C[0][i] = 1;
    for (ll k = 1; k <= i; k++) {
      C[k][i] = (C[k][i - 1] + C[k - 1][i - 1]) % MOD;
    }
  }
  S[0][0] = 1;
  for (ll i = 1; i < MAX; i++) {
    S[i][0] = 0;
    S[0][i] = 0;
    for (ll k = 1; k <= i; k++) {
      S[k][i] = (k * S[k][i - 1] + S[k - 1][i - 1]) % MOD;
    }
  }
  ll n;
  while (cin >> n) {
    // cerr << "> " << n << endl;
    ll answer = 0;
    for (ll i = 0; i < n; i++) {
      ll x = C[i][n];
      ll y = 0;
      for (ll j = 0; j <= i; j++) {
        y = (y + S[j][i]) % MOD;
      }
      // cerr << i << ' ' << x << " " << y << endl;
      answer = (answer + (x * y) % MOD) % MOD;
    }
    cout << answer << endl;
  }
}
