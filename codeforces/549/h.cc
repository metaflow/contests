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

// invariant: answer is within (a, b], f(a) = false, f(b) = true
double binary_search_lower(double a, double b, function<bool(double)> f) {
  int i = 0;
  while (round(b * 1000000000) != round(a * 1000000000) && i < 100) {
    i++;
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
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  double _ = 0;
  if (a * d != b * c) {
    if (a * d < b * c) {
      swap(a, b);
      swap(c, d);
    }
    double t = max(max(max(abs(a), abs(b)), abs(c)), abs(d));
    _ = binary_search_lower(0, t, [&](double x) {
      const int r[] = {-1, 1};
      for (int sa = 0; sa < 2; sa++)
      for (int sb = 0; sb < 2; sb++)
      for (int sc = 0; sc < 2; sc++)
      for (int sd = 0; sd < 2; sd++) {
        double v = (a + x * r[sa]) * (d + x * r[sd]) -
        (b + x * r[sb]) * (c + x * r[sc]);
        if (v < 0) return true;
      }
      return false;
    });
  }
  cout << setprecision(9) << fixed << _ << endl;
}


