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

// straighforward Gaussian elimination O(n^3)
// x + y = a    ->  [[1 1 a],
// 2x + 1y = b  ->   [2 1 b]]
vector<double> solve(vector<vd> m) {
  ll n = m.size();
  for (ll i = 0; i < n; i++) {
    // find row from i with largest value at i
    ll tr = i;
    for (ll r = i + 1; r < n; r++) {
      if (m[r][i] > m[tr][i]) tr = r;
    }
    // swap with row i
    swap(m[i], m[tr]);
    // eliminate i from all rows below
    for (ll r = i + 1; r < n; r++) {
      for (ll c = n; c >= i; c--) {
        m[r][c] -= m[i][c] * m[r][i] / m[i][i]; // be carefull
      }
    }
  }
  vd result(n);
  // restore
  for (ll i = n - 1; i >= 0; i--) {
    double t = m[i][n];
    for (ll j = i + 1; j < n; j++) t -= m[i][j] * result[j];
    t /= m[i][i]; // be carefull
    result[i] = t;
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    vector<llu> v(1500);
    for (size_t i = 0; i < v.size(); i++) cin >> v[i];
    vector<vector<double>> m(7);
    for (ll i = 0; i < 7; i++) {
      m[i].resize(8);
      ll x = i + 1;
      m[i][0] = 1;
      for (ll j = 1; j < 7; j++) m[i][j] = m[i][j - 1] * x;
      m[i][7] = v[i];
      // for (ll j = 0; j < 7; j++) {
      //   if (j) cout << ' ';
      //   cout << m[i][j];
      // }
      // cout << endl;
    }
    auto roots = solve(m);
    vi a;
    bool ok = true;
    for (auto d : roots) {
      a.emplace_back(round(d));
      ok = ok && (a.back() >= 0) && (a.back() < 1001);
    }
    for (size_t i = 0; i < v.size() && ok; i++) {
      llu t = 0;
      llu x = 1;
      for (ll j = 0; j < 7; j++) {
        t += a[j] * x;
        x *= i + 1;
      }
      ok = ok && (t == v[i]);
    }
    if (ok) {
      for (ll i = 0; i < 7; i++) {
        if (i) cout << ' ';
        cout << a[i];
      }
      cout << endl;
    } else {
      cout << "This is a smart sequence!" << endl;
    }
  }
}
