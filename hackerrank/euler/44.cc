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
  vl v;
  for (l i = 1; i <= e6 * 2; i++) {
    v.emplace_back(i * (3 * i - 1) / 2);
  }
  l n, k;
  while (cin >> n >> k) {
    // cout << n << " " << k << endl;
    l a = 0, b = 0;
    for (l i = k; i < n - 1; i++) {
      l r = 0;
      // cout << v[i] << endl;
      l t = v[i] - v[i - k];
      while (v[a] < t) a++;
      if (v[a] == t) r = v[i];
      t = v[i] + v[i - k];
      while (v[b] < t) b++;
      if (v[b] == t) r = v[i];
      if (r != 0) cout << r << endl;
    }
  }
}
