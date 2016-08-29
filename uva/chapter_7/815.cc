#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int m, n;
  int tc = 0;
  while (cin >> m >> n, m) {
    tc++; printf("Region %d\n", tc);
    vector<ll> levels(m * n);
    double f = INF;
    for (int i = 0; i < m * n; i++) {
      cin >> levels[i];
      if (f > levels[i]) f = levels[i];
    }
    ll v; cin >> v;
    double t = INF; // invariant is f <= x, t > x
    while (round(f * 100) != round(t * 100)) {
      double m = (f + t) / 2;
      double a = 0;
      for (auto l : levels) {
        if (m > l) a += 100 * (m - l);
      }
      if (abs(a - v) < 1e-9) {
        f = t = m; break;
      }
      if (a < v) {
        f = m;
      } else {
        t = m;
      }
    }
    double flooded = 0;
    for (auto l : levels) if (l < f) flooded++;
    printf("Water level is %.2f meters.\n", round(f * 100) / 100);
    printf("%.2f percent of the region is under water.\n\n",
          (flooded * 100) / (n * m));
  }
}
