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

// invariant: answer is within (a, b], f(a) = false, f(b) = true
double binary_search_lower(double a, double b, function<bool(double)> f) {
  for (int i = 0; i < 34; i++) {
    double m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vd a(n);
    double d, u;
    for (l i = 0; i < n; i++) cin >> a[i];
    d = u = a[0];
    for (auto q : a) {
      d = min(d, q);
      u = max(u, q);
    }
    auto x = binary_search_lower(d, u, [&](double x) {
      double top = 0, bottom = 0;
      double best_top = 0, best_bottom = 0;
      for (auto v : a) {
        top += v - x; if (top < 0) top = 0;
        best_top = max(best_top, top);
        bottom += v - x; if (bottom > 0) bottom = 0;
        best_bottom = min(best_bottom, bottom);
      }
      return (abs(best_top) < abs(best_bottom));
    });
    double top = 0, bottom = 0;
    double best_top = 0, best_bottom = 0;
    for (auto v : a) {
      top += v - x; if (top < 0) top = 0;
      best_top = max(best_top, top);
      bottom += v - x; if (bottom > 0) bottom = 0;
      best_bottom = min(best_bottom, bottom);
    }
    cout << fixed << setprecision(15)
         << max(abs(best_top), abs(best_bottom)) << endl;
  }
}
