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
  cin >> n;
  vll v(n);
  for (ll i = 0; i < n; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  ll q; cin >> q;
  while (q--) {
    ll x; cin >> x;
    auto a = lower_bound(v.begin(), v.end(), x);
    cout << (a - v.begin()) << endl;
  }
}
