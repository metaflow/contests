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

// [from, to]
l bounded_lis(vl& v, l from, l to, l times) {
  vl lis;
  for (l i = 0; i < times; i++) {
    for (auto a : v) {
      if (a < from || a > to) continue;
      auto it = upper_bound(lis.begin(), lis.end(), a);
      if (it == lis.end()) {
        lis.emplace_back(a);
      } else {
        *it = a;
      }
    }
  }
  return lis.size();
}

const l MAX = 301;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, T;
  while (cin >> n >> T) {
    vl v(n);
    vl counts(301);
    for (l i = 0; i < n; i++) {
      cin >> v[i];
      counts[v[i]]++;
    }
    l m = 0;
    for (l i = 0; i < 301; i++) {
      if (counts[i] > counts[m]) m = i;
    }
    l best = bounded_lis(v, 0, MAX, min(T, n + 1));
    vl x(n + 1), y(n + 1);
    for (l i = 0; i <= n; i++) {
      x[i] = bounded_lis(v, 0, m, i);
      y[i] = bounded_lis(v, m, MAX, i);
    }
    for (l i = 0; i <= min(n, T); i++) {
      for (l j = 0; j <= min(n, T - i); j++) {
        best = max(best, x[i] + (T - i - j) * counts[m] + y[j]);
      }
    }
    cout << best << endl;
  }
}
