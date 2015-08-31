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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n; cin >> n;
  vvll positions(n);
  vll points(n);
  for (ll i = 0; i < n; i++) cin >> points[i];
  ll k; cin >> k;
  for (ll i = 0; i < k; i++) {
    ll j; cin >> j; j--;
    positions[j].emplace_back(i);
  }
  for (ll i = 0; i < n; i++) {
    ll s = positions[i].size();
    for (ll j = 0; j < s; j++) {
      positions[i].emplace_back(positions[i][j] + k);
    }
  }
  ll q; cin >> q;
  for (ll i = 0; i < q; i++) {
    ll f, t; cin >> f >> t;
    f--; t = f + t - 1;
    ll answer = 0;
    for (ll i = 0; i < n; i++) {
      auto l = lower_bound(positions[i].begin(), positions[i].end(), f);
      auto u = upper_bound(positions[i].begin(), positions[i].end(), t);
      if (l != u) answer += points[i];
    }
    cout << answer << endl;
  }
}

