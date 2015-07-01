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
  ll n, w;
  while (cin >> n >> w) {
    vll a(2 * n);
    for (size_t i = 0; i < a.size(); i++) {
      cin >> a[i];
    }
    sort(a.begin(), a.end());
    ll x = min(min(a[0] * 2, a[n]) * 3 * n, 2 * w);
    cout << x / 2;
    if (x % 2) cout << ".5";
    cout << endl;
  }
}
