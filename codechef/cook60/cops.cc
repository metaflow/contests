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
    ll m, x, y;
    cin >> m >> x >> y;
    x *= y;
    bitset<100> b;
    for (ll i = 0; i < m; i++) {
      ll l; cin >> l; l--;
      for (ll j = max(0LL, l - x); j < min(100LL, l + x + 1); j++) b.set(j);
    }
    cout << (100 - b.count()) << endl;
  }
}
