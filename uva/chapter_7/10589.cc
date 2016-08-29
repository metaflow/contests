#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

double distance(double x, double y, double x2, double y2) {
  return pow(x - x2, 2) + pow(y - y2, 2);
}

int main() {
  ll n, a;
  double t = sqrt(3) / 2;
  double l = 1 - t;
  while (cin >> n >> a, n) {
    double r = a;
    double x, y;
    int m = 0;
    for (int i = 0; i < n; i++) {
      // cin >> x >> y;
      scanf("%lf%lf", &x, &y);
      x /= r;
      y /= r;
      double xx = pow(x, 2);
      double dx = pow(1 - x, 2);
      double yy = pow(y, 2);
      double dy = pow(1 - y, 2);
      if (xx + yy <= 1 &&
          xx + dy <= 1 &&
          dx + yy <= 1 &&
          dx + dy <= 1) m++;
    }

    double s = (r * r * m) / n;
    printf("%.5lf\n", s);
  }
}
