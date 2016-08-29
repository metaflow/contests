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
  while (cin >> n, n) {
    vll d(n);
    for (ll i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end(), greater<ll>());
    ll sum = 0;
    bool ok = true;
    for (ll i = 0; i < n && ok; i++) {
      sum += d[i];
      ll t = (i * (i + 1)) + accumulate(d.begin() + i + 1, d.end(), 0,
          [&] (const ll& a, const ll& b) {
            return a + min(b, i + 1);
          });
      ok = ok && (sum <= t);
    }
    ok = (sum % 2 == 0) && ok;
    if (ok) {
      cout << "Possible" << endl;
    } else {
      cout << "Not possible" << endl;
    }
  }
}
