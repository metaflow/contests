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
const l MAX = 301;
vl as;

l lis(function<bool(l)> p) {
  vl seq;
  for (auto a : as) {
    if (!p(a)) continue;
    auto i = upper_bound(seq.begin(), seq.end(), a);
    if (i == seq.end()) {
      seq.push_back(a);
    } else {
      *i = a;
    }
  }
  return seq.size();
}

vvl mmax(vvl a, vvl b) {
  l n = a.size();
  vvl c(n, vl(n));
  for (l i = 0; i < n; i++) {
    for (l j = 0; j < n; j++) {
      for (l k = 0; k < n; k++) {
        if (as[k] < as[i] || as[k] > as[j]) continue;
        c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
      }
    }
  }
  return c;
}

vvl pow_max(vvl a, l t) {
  l n = a.size();
  vvl r;
  bool identity = true;
  while (t) {
    if (t % 2) {
      if (identity) {
        identity = false;
        r = a;
      } else {
        r = mmax(r, a);
      }
    }
    a = mmax(a, a);
    t /= 2;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, t;
  while (cin >> n >> t) {
    as.resize(n);
    for (l i = 0; i < n; i++) cin >> as[i];
    vvl m(n, vl(n));
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < n; j++) {
        l a = as[i], b = as[j];
        m[i][j] = lis([&a,&b](const l& x) {return x >= a && x <= b; });
      }
    }
    m = pow_max(m, t);
    l best = 0;
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < n; j++) {
        best = max(best, m[i][j]);
      }
    }
    cout << best << endl;
  }
}
