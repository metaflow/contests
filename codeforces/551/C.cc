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

// invariant: answer is within (a, b], f(a) = false, f(b) = true
ll binary_search_lower(ll a, ll b, function<bool(ll)> f) {
  while (b - a > 1) {
    ll m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m;
  while (cin >> n >> m) {
    vll v(n);
    ll low = 0;
    for (ll i = 0; i < n; i++) {
      cin >> v[i];
      if (v[i]) low = i + 1;
    }
    auto a = binary_search_lower(low, 1000000000000000LL, [&] (ll x) {
      vll t = v;
      ll mm = 0;
      ll additional = 0;
      for (ll i = t.size() - 1; i >= 0; i--) {
        if (t[i] <= additional) {
          additional -= t[i];
          continue;
        }
        t[i] -= additional; additional = 0;
        ll load = x - i - 1;
        ll k = (t[i] + load - 1) / load;
        mm += k;
        if (mm > m) return false;
        additional = load * k - t[i];
      }
      return true;
    });
    cout << a << endl;
  }
}
