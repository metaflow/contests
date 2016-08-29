#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  double l, w, h, t;
  while (cin >> l >> w >> h >> t) {
    t = tan(M_PI * t / 180);
    double v;
    if (h > t * l) {
      v = l * h - l * l * 0.5 * t;
    } else {
      v = 0.5 * h * h / t;
    }
    printf("%.3f mL\n", v * w);
  }
}
