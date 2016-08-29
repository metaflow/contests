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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  bool first = true;
  while (cin >> n) {
    if (!first) cout << endl;
    first = false;
    vector<vll> m(n);
    for (ll i = 0; i < n; i++) m[i].resize(n, 0);
    ll x = 0, y = n / 2;
    for (ll i = 1; i <= n * n; i++) {
      m[x][y] = i;
      ll a = (x - 1 + n) % n;
      ll b = (y + 1) % n;
      if (m[a][b]) { a = (x + 1) % n; b = y; };
      x = a; y = b;
    }
    ll sum = 0;
    for (ll i = 0; i < n; i++) sum += m[0][i];
    cout << "n=" << n << ", sum=" << sum << endl;
    ll p = 1;
    ll t = n * n;
    while (t) { p++; t /= 10; }
    // cout << setfill(' ') << setw(p);
    for (ll i = 0; i < n; i++) {
      for (ll j = 0; j < n; j++) {
        cout << setfill(' ') << setw(p) << m[i][j];
      }
      cout << endl;
    }
  }
}
