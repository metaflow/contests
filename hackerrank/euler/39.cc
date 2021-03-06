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
const l MAX = 5 * e6 + 1;

l gcd(l a, l b) {
  while (b) {
    l t = b;
    b = a % b;
    a = t;
  }
  return a;
}

l lcm(l a, l b) {
  return a * b / gcd(a, b);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vl p(MAX);
  for (l m = 1; m < 3000; m++) {
    for (l n = 1; n < m; n++) {
      if (gcd(n, m) != 1) continue;
      if ((m - n) % 2 == 0) continue;
      for (l k = 1; ; k++) {
        l t = 2 * k * m * (m + n);
        if (t >= MAX) break;
        p[t]++;
      }
    }
  }
  vl a(MAX);
  for (l i = 1; i < MAX; i++) {
    a[i] = i;
    if (p[i] <= p[a[i - 1]]) a[i] = a[i - 1];
  }
  l tcc; cin >> tcc;
  while (tcc--) {
    l n; cin >> n;
    cout << a[n] << endl;
  }
}
