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

bool multiplier(ll n, ll k) {
  ll left = k;
  vb used(k);
  for (ll i = 1; i < 10; i++) {
    ll t = n * i;
    while (t) {
      ll a = t % 10;
      t /= 10;
      if (a == 0 || a > k) return false;
      if (used[a]) return false;
      left--;
      used[a] = true;
    }
    if (left == 0) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, k;
  cin >> n >> k;
  for (ll i = 2; i < n; i++) {
    if (multiplier(i, k)) cout << i << endl;
  }
}
