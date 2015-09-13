// time 20:00
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
const ll e9 = 1000000000;
const ll MOD = e9 + 9;

ll pow_mod(ll base, ll power, ll mod) {
  ll r = 1;
  while (power) {
    if (power % 2) r = (r * base) % mod;
    base = (base * base) % mod;
    power /= 2;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m, k;
  while (cin >> n >> m >> k) {
    ll r = k * (n - m);
    r = (n - r) / k;
    if (r < 0) r = 0;
    ll answer = k * (pow_mod(2, r + 1, MOD) - 2 + MOD) % MOD + (m - r * k);
    cout << answer % MOD << endl;
  }
}
