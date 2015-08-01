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

ll f(const ll a, const ll n) {
  return (a * 10) % n;
}

ll cycle_length(ll n) {
  ll t = 1;
  ll u = f(t, n);
  while (u != t) {
    t = f(t, n);
    u = f(f(u, n), n);
  }
  if (u == 0) return 0;
  int c = 1;
  t = f(t, n);
  while (t != u) {
    c++;
    t = f(t, n);
  }
  return c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vll t(10001);
  ll best_i = 3, best = 1;
  for (int i = 4; i < 10001; i++) {
    t[i] = best_i;
    int _ = cycle_length(i);
    if (_ > best) {
      best = _;
      best_i = i;
      // cerr << " " << i << endl;
    }
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    cout << t[n] << endl;
  }
}
