#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-8;

int main() {
  double D, V;
  while (cin >> D >> V, D > EPS) {
    double f = 0;
    double t = D;
    while (round(f * 1000) != round(t * 1000) && (t - f) > EPS) {
      double d = (f + t) / 2;
      double e = M_PI / 4  * (pow(D, 3) - pow(d, 3) -
        (pow(D, 2) * (D - d) + (pow(D, 2) - pow(d, 2)) * d) / 3);
      if (e > V) {
        f = d;
      } else {
        t = d;
      }
    }
    printf("%.3f\n", f);
  }
}
