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
  l n, k;
  while (cin >> n >> k) {
    vl v(n);
    for (l i = 0; i < n; i++) cin >> v[i];
    l t = 0;
    for (auto i : v) t = max(i, t);
    vvl layers(t + 1);
    for (l i = 0; i < n; i++) layers[v[i]].push_back(i);
    // cout << layers[0].size() << ".";
    bool ok = layers[0].size() == 1;
    for (l i = 1; i <= t; i++) {
      auto d = i == 1 ? k : k - 1;
      ok = ok && (layers[i].size() <= layers[i - 1].size() * d);
    }
    if (ok) {
      cout << n - 1 << endl;
      for (l i = 1; i <= t; i++) {
        auto d = i == 1 ? k : k - 1;
        for (l j = 0; j < layers[i].size(); j++) {
          cout << layers[i - 1][j / d] + 1 << " "
               << layers[i][j] + 1 << endl;
        }
      }
    } else {
      cout << -1 << endl;
    }
  }
}
