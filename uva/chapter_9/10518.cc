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

vvll matrix_multiply(vvll a, vvll b, ll mod) {
  ll n = a.size();
  ll k = b.size();
  ll m = b[0].size();
  vvll c(n);
  for (ll i = 0; i < n; i++) c[i].resize(m);
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      for (ll q = 0; q < k; q++) {
        c[i][j] = (c[i][j] + a[i][q] * b[q][j]) % mod;
      }
    }
  }
  return c;
}

vvll matrix_power_mod(vvll a, ll power, ll mod) {
  ll n = a.size();
  vvll b(a);
  for (ll i = 0; i < n; i++) { b[i].resize(n); b[i][i] = 1; };
  while (power) {
    if (power & 1) b = matrix_multiply(b, a, mod);
    a = matrix_multiply(a, a, mod);
    power /= 2;
  }
  return b;
}

ll fib(ll n, ll mod) {
  vvll a = {{1, 1}, {1, 0}};
  return matrix_power_mod(a, n, mod)[0][1];
}

ll c(ll n, ll mod) {
  return (fib(n, mod) * 2 - 1 + mod) % mod;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, mod;
  ll tc = 0;
  while (cin >> n >> mod, mod) {
    tc++;
    cout << "Case " << tc << ": " << n << " " << mod
         << " " << c(n, mod) << endl;
  }
}
