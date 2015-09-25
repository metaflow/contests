#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vvb matches(n, vb(n));
    vl price(n);
    for (l i = 0; i < n; i++) cin >> price[i];
    for (l i = 0; i < m; i++) {
      l a, b; cin >> a >> b; a--; b--;
      matches[a][b] = matches[b][a] = true;
    }
    l best = INF;
    for (l i = 0; i < n; i++) {
      for (l j = i + 1; j < n; j++) {
        if (!matches[i][j]) continue;
        for (l k = j + 1; k < n; k++) {
          if (matches[i][k] && matches[j][k]) {
            best = min(best, price[i] + price[j] + price[k]);
          }
        }
      }
    }
    if (best == INF) best = -1;
    cout << best << endl;
  }
}
