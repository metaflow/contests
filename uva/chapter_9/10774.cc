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
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll count = 0;
    ll a; cin >> a;
    while (true) {
      ll t, m;
      t = m = a;
      while (m) {
        ll l = (m & (-m));
        if (m == l) break;
        m -= l;
      }
      a = ((a - m) << 1) + 1;
      if (a == t) break;
      count++;
    }
    if (count == 0) count = 1;
    cout << "Case " << tc << ": " << count << " " << a << endl;
  }
}
