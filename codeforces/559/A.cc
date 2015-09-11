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
const int MAX = 3001;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vll f(MAX);
  f[1] = 1;
  for (ll i = 2; i < MAX; i++) f[i] = f[i - 1] + 2 * i - 1;
  ll a;
  while (cin >> a) {
    vll v(6);
    v[0] = a;
    for (ll i = 1; i < 6; i++) cin >> v[i];
    cout << f[v[0] + v[1] + v[2]] - f[v[0]] - f[v[2]] - f[v[4]] << endl;
  }
}
