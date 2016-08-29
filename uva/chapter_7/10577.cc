#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-8;

struct point {
  double x, y;
  point operator *(double m) {
    point r;
    r.x = x * m;
    r.y = y * m;
    return r;
  }

  point operator +(point b) {
    point r{x + b.x, y + b.y};
    return r;
  }
  point operator -(point b) {
    point r{x - b.x, y - b.y};
    return r;
  }

  friend ostream& operator <<(ostream& os, const point &a) {
    return os << a.x << " " << a.y;
  }
};

int main() {
  int n;
  int tc = 0;
  while (cin >> n, n) {
    tc++;
    point A, B, O;
    cin >> O.x >> O.y >> A.x >> A.y >> B.x >> B.y;
    point a = A - O;
    point pa{-a.y, a.x};
    point b = B - O;
    point D = O + a * 0.5;
    point C = O + b * 0.5;
    double u = 0;
    if (abs(b.y) < EPS) {
      u = (D.x - C.x) / a.y;
    } else {
      double k = b.x / b.y;
      u = (k * (C.x - D.x) + C.y - D.y) / (a.x - k * a.y);
    }
    point G = D + pa * u;
    double angle = 2 * M_PI / n;
    point top_right = O;
    point bottom_left = O;
    a = O - G;
    for (int i = 1; i < n; i++) {
      point t;
      t.x = a.x * cos(i * angle) + a.y * sin(i * angle);
      t.y = - a.x * sin(i * angle) + a.y * cos(i * angle);
      point H = G + t;
      top_right.x = max(top_right.x , H.x);
      top_right.y = max(top_right.y , H.y);
      bottom_left.x = min(bottom_left.x, H.x);
      bottom_left.y = min(bottom_left.y, H.y);
    }
    printf("Polygon %d: %.3f\n", tc,
      (top_right.x - bottom_left.x) * (top_right.y - bottom_left.y));
  }
}
