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
  ll n; cin >> n;
  vll v(n);
  for (ll i = 0; i < n; i++) cin >> v[i];
  ll best = 0;
  for (ll rx = 0; rx < n; rx++) {
    for (ll ly = rx + 1; ly <= rx + 2; ly++) {
      ll x = rx;
      ll y = ly;
      ll sum = 0;
      while (x >= 0 && y < n) {
        sum += v[x] * v[y];
        best = max(best, sum);
        if (sum < 0) sum = 0;
        x--; y++;
      }
    }
  }
  cout << best << endl;
}
