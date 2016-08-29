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

vvll matrix_multiply(vvll a, vvll b) {
  ll n = a.size();
  ll k = b.size();
  ll m = b[0].size();
  vvll c(n);
  for (ll i = 0; i < n; i++) c[i].resize(m);
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      for (ll q = 0; q < k; q++) {
        c[i][j] = (c[i][j] + a[i][q] * b[q][j]);
      }
    }
  }
  return c;
}

// m should be square
vvll matrix_power(vvll m, ll power) {
  ll n = m.size();
  vvll o(n);
  for (ll i = 0; i < n; i++) { o[i].resize(n); o[i][i] = 1; }
  while (power) {
    if (power % 2) o = matrix_multiply(o, m);
    m = matrix_multiply(m, m);
    power /= 2;
  }
  return o;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll p, q, n;
  while (cin >> p >> q >> n) {
    if (n == 0) {
      cout << 2 << endl;
      continue;
    }
    if (n == 1) {
      cout << p << endl;
      continue;
    }
    ll f1 = p;
    ll f2 = p * p - 2 * q;
    vvll m = {{p, -q}, {1, 0}};
    auto a = matrix_multiply(matrix_power(m, n - 2), {{f2}, {f1}});
    cout << a[0][0] << endl;
  }
}
