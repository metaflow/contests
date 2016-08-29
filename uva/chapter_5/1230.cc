#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll pow_mod(ll base, ll power, ll mod) {
  if (power == 0) return 1;
  if (power % 2 == 0) {
    ll t = pow_mod(base, power / 2, mod);
    return (t * t) % mod;
  }
  return (base * pow_mod(base, power - 1, mod)) % mod;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    ll x, y, n;
    cin >> x >> y >> n;
    cout << pow_mod(x, y, n) << endl;
  }
}
