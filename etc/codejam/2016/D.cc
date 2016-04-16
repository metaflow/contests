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

// (base^power) % mod, safe for l near max
l powl(l base, l power) {
  l r = 1;
  while (power) {
    if (power % 2) r *= base;
    base *= base;
    power /= 2;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    cout << "Case #" << tc << ": ";
    l k, c, s; cin >> k >> c >> s;
    vl pick;
    if (c == 1) {
      for (l i = 1; i <= k; i++) pick.emplace_back(i);
    } else {
      l m = powl(k, c - 1);
      if (k % 2) pick.emplace_back(k);
      for (l i = 2; i <= k; i += 2) {
        pick.emplace_back(i + m * (i - 2));
      }
      sort(pick.begin(), pick.end());
    }
    if (pick.size() > s) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      for (l i = 0; i < pick.size(); i++) {
      if (i) cout << " ";
       cout << pick[i];
      }
      cout << endl;
    }
  }
}
