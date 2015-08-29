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
  ll n;
  while (cin >> n) {
    vll v(n), ff(n), bw(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    ff[0] = 1;
    for (ll i = 1; i < n; i++) ff[i] = min(ff[i - 1] + 1, v[i]);
    bw[n - 1] = 1;
    for (ll i = n - 2; i >= 0; i--) bw[i] = min(bw[i + 1] + 1, v[i]);
    ll answer = 0;
    for (ll i = 0; i < n; i++) answer = max(answer, min(bw[i], ff[i]));
    cout << answer << endl;
  }
}
