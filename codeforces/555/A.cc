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
  ll n, m;
  while (cin >> n >> m) {
    ll answer = n - 1;
    for (ll i = 0; i < m; i++) {
      ll k; cin >> k;
      ll a; cin >> a;
      bool f = (a != 1);
      for (ll i = 0; i < k - 1; i++) {
        ll b; cin >> b;
        f = f || (b - a != 1);
        if (f) { answer++; continue; }
        answer--;
        a = b;
      }
    }
    cout << answer << endl;
  }
}
