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

double dist(double x, double y) {
  return pow(pow(x, 2) + pow(y, 2), 0.5);
}

int sign(ll n) {
  if (n < 0) return - 1;
  if (n > 0) return 1;
  return 0;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll x1, x2, y1, y2;
  while (cin >> x1 >> y1 >> x2 >> y2) {
    ll x = x2 - x1;
    ll y = y2 - y1;
    int n; cin >> n;
    bool ok = false;
    vector<pair<ll, ll>> v;
    for (ll i = 0; i < n; i++) {
      ll x, y;
      cin >> x >> y;
      v.emplace_back(x, y);
    }
    if (x == 0 && y == 0) {
      cout << "YES" << endl;
      continue;
    }
    for (ll i = 0; i < n; i++) {
      ll xa = v[i].first; ll ya = v[i].second;
      ll ma = x * ya - y * xa;
      if (ma == 0) {
        if (x * xa + y * ya > 0) {
          ok = true;
          break;
        }
        continue;
      }
      double sa = asin(double(abs(ma)) / dist(x, y) / dist(xa, ya));
      if (x * xa + y * ya < 0) sa = M_PI - sa;
      for (ll j = 0; j < n; j++) {
        ll xb = v[j].first; ll yb = v[j].second;
        ll mb = x * yb - y * xb;
        if (sign(mb) * sign(ma) >= 0) continue;
        double sb = asin(double(abs(mb)) / dist(x, y) / dist(xb, yb));
        if (x * xb + y * yb < 0) sb = M_PI - sb;
        if (sb + sa < M_PI) ok = true;
      }
    }
    if (ok) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
