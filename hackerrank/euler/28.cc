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
const ll MOD = 1000000007;

ll modp(ll n, ll p) {
  ll a = 1;
  for (ll i = 0; i < p; i++) a = (a * n) % MOD;
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n; n = (n - 1) / 2;
    n = n % MOD;
    ll a = (1 + 10 * modp(n, 2) + (16 * modp(n, 3) + n * 26) % MOD * 333333336) % MOD;
    cout << a << endl;
  }
}
