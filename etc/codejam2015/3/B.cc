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

struct bar {
  ll base, top, bottom;
};

ll sign(ll n) {
  if (n < 0) return -1;
  if (n == 0) return 0;
  return 1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, k; cin >> n >> k;
    vector<bar> v(k);
    vll sums(n - k + 1);
    for (ll i = 0; i < n - k + 1; i++) cin >> sums[i];
    for (ll i = 0; i < n - k; i++) {
      ll j = i % k;
      ll d = sums[i + 1] - sums[i];
      v[j].base += d;
      v[j].top = max(v[j].top, v[j].base);
      v[j].bottom = min(v[j].bottom, v[j].base);
    }
    ll s0 = 0;
    for (auto &t : v) { t.base = -t.top; s0 += t.base; }
    ll d_sum = sums[0] - s0;
    for (auto &t : v) {
      t.base += d_sum / k;
      s0 += d_sum / k;
    }
    d_sum = sign(sums[0] - s0);
    for (auto &t : v) {
      if (s0 == sums[0]) break;
      t.base += d_sum;
      s0 += d_sum;
    }
    assert(s0 == sums[0]);
    // for (auto t : v) cout << t.bottom << " " << t.base << " " << t.top << endl;
    ll a = v[0].top + v[0].base;
    ll b = v[0].bottom + v[0].base;
    for (auto t : v) {
      a = max(a, t.top + t.base);
      b = min(b, t.bottom + t.base);
    }
    ll to_rise = 0, to_low = 0;
    bool unmovable = false;
    for (auto t : v) {
      if (t.bottom + t.base == b) {
        if (t.top + t.base == a) {
          unmovable = true;
          break;
        }
        to_rise++;
      } else if (t.bottom + t.base >= b + 2) {
        to_low += t.bottom + t.base - (b + 1);
      }
    }
    if (!unmovable && (to_low >= to_rise)) b++;
    cout << "Case #" << tc << ": " << (a - b) << endl;
  }
}
