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

const int MAX = 13;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vi d(MAX), f(MAX);
  d[0] = 1; d[1] = 0;
  f[0] = 0; f[1] = 1;
  for (ll i = 2; i < MAX; i++) {
    d[i] = (i - 1) * (d[i - 1] + d[i - 2]);
    f[i] = i * f[i - 1];
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll i; cin >> i;
    cout << d[i] << '/' << f[i] << endl;
  }
}
