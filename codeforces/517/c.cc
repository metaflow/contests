#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 10001;
const double EPS = 1e-12;

int main() {
  int n;
  while (cin >> n) {
    vector<vector<double>> v(n); // [i][j] probatility i is <= j
    for (int i = 0; i < n; i++) {
      v[i].resize(MAX, 0);
      int l, r;
      cin >> l >> r;
      double d = r - l + 1;
      d = 1 / d;
      double s = 0;
      for (int j = l; j < r; j++) {
        s += d;
        v[i][j] = s;
      }
      for (int j = r; j < MAX; j++) v[i][j] = 1;
    }
    // [i][j] probabily all except i has value <= j
    vector<vector<double>> e(n);
    for (int i = 0; i < n; i++) {
      e[i].resize(MAX, 1);
      for (int p = 0; p < MAX; p++) {
        for (int j = 0; j < n; j++) {
          if (j == i) continue;
          e[i][p] *= v[j][p];
        }
      }
    }
    vector<vector<double>> m(n); // [i][j] expected value of max value of all
    // except i given that it <= j
    for (int i = 0; i < n; i++) {
      m[i].resize(MAX, 0);
      for (int p = 1; p < MAX; p++) {
        m[i][p] = m[i][p - 1] + p * (e[i][p] - e[i][p - 1]);
      }
      for (int p = 1; p < MAX; p++) {
        if (e[i][p] > EPS) m[i][p] /= e[i][p];
      }
    }
    double sum = 0;
    double sum_p = 0;
    for (int i = 0; i < n; i++) {
      for (int p = 1; p < MAX; p++) {
        double t = (v[i][p] - v[i][p - 1]);
        if (t < EPS) continue;
        double z = t * e[i][p - 1];
        sum += z * m[i][p - 1];
        sum_p += z;
        double a = e[i][p] - e[i][p - 1];
        z = t * a * t / (t + a);
        sum += z * m[i][p];
        sum_p += z;
      }
    }
    printf("%.9f\n", sum / sum_p);
  }
}
