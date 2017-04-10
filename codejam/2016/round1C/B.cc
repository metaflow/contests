#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    cout << "Case #" << tc << ": ";
    l n; l total;
    cin >> n >> total;
    vvl m(n, vl(n));
    for (l i = 0; i < n; i++) {
      for (l j = i + 1; j < n; j++) m[i][j] = 1;
    }
    l t = total;
    t--;
    l mult = 1;
    l sum = 1;
    for (l i = 1; i < n - 1; i++) {
      if (t % 2) {
        sum += mult;
      } else {
        m[i][n - 1] = 0;
      }
      mult *= 2;
      t /= 2;
    }
    if (sum < total) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << "POSSIBLE" << endl;
      for (l i = 0; i < n; i++) {
        for (l j = 0; j < n; j++) {
          cout << m[i][j];
        }
        cout << endl;
      }
    }
  }
}
