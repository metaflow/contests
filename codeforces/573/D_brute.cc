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

ll f(ll k, vll& bears, vll& hourses, vll& at, vb& used) {
  if (k == -1) return 0;
  ll r = -INF;
  for (ll i = 0; i < hourses.size(); i++) {
    if (at[k] == i || used[i]) continue;
    used[i] = true;
    r = max(r, bears[k] * hourses[i] + f(k - 1, bears, hourses, at, used));
    used[i] = false;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, q;
  cin >> n >> q;
  vll bears(n);
  vll hourses(n);
  vll at(n);
  for (ll i = 0; i < n; i++) cin >> bears[i];
  for (ll i = 0; i < n; i++) cin >> hourses[i];
  for (ll i = 0; i < n; i++) at[i] = i;
  for (ll i = 0; i < q; i++) {
    ll a, b; cin >> a >> b;
    a--; b--;
    swap(at[a], at[b]);
    vb used(n);
    cout << f(n - 1, bears, hourses, at, used) << endl;
  }
}
