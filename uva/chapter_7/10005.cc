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
};

double square_distance(const point a, const point b) {
  return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

point center(point a, point b, double rr) {
  double ab = square_distance(a, b);
  double k = sqrt(rr / ab - 0.25);
  point o;
  o.x = (a.x + b.x) / 2 + k * (b.y - a.y);
  o.y = (a.y + b.y) / 2 + k * (a.x - b.x);
  return o;
}

int main() {
  int n;
  while (cin >> n, n) {
    vector<point> v(n);
    double r;
    for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    cin >> r;
    r *= r;
    bool ok = true;
    for (int i = 0; i < n && ok; i++) {
      for (int j = i + 1; j < n && ok; j++) {
        ok = (square_distance(v[i], v[j]) - 4 * r < EPS);
      }
    }

    if (ok) {
      ok = false;
      for (int i = 0; i < n && !ok; i++) {
        for (int j = 0; j < n && !ok; j++) {
          if (i == j) continue;
          auto c = center(v[i], v[j], r);
          ok = true;
          for (int k = 0; k < n; k++) {
            if (square_distance(v[k], c) - r > EPS) {
              ok = false;
              break;
            }
          }
        }
      }
    }

    if (ok || n == 1) {
      cout << "The polygon can be packed in the circle." << endl;
    } else {
      cout << "There is no way of packing that polygon." << endl;
    }
  }
}
