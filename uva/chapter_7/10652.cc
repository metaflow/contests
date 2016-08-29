#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct point {
  double x, y;
};

using vp = vector<point>;

double cross_product(point o, point a, point b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double distance(point a, point b) {
  return pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5);
}

vp build_hull(vp& dots) {
  int k = 0;
  for (size_t i = 1; i < dots.size(); i++) {
    if (dots[i].x > dots[k].x) continue;
    if (dots[i].x == dots[k].x && dots[i].y > dots[k].y) continue;
    k = i;
  }
  swap(dots[0], dots[k]);
  point &o = dots[0];
  sort(dots.begin() + 1, dots.end(), [o] (const point &a, const point &b) {
    if (cross_product(o, a, b) == 0) return distance(o, a) < distance(o, b);
    return atan2(a.y - o.y, a.x - o.x) < atan2(b.y - o.y, b.x - o.x);
  });
  stack<point> s;
  s.push(dots[0]);
  s.push(dots[1]);
  for (size_t i = 2; i < dots.size(); i++) {
    point a = dots[i];
    while (s.size() > 1) {
      point b = s.top(); s.pop();
      point c = s.top();
      if (cross_product(c, b, a) > 0) {
        s.push(b);
        break;
      }
    }
    s.push(a);
  }
  vp hull;
  while (!s.empty()) {
    hull.emplace_back(s.top());
    s.pop();
  }
  return hull;
}

double area(vp p) {
  double a = 0;
  for (size_t i = 2; i < p.size(); i++) {
    a += cross_product(p[0], p[i - 1], p[i]);
  }
  return abs(a / 2);
}

int main() {
  int tcc; cin >> tcc;
  while (tcc--) {
    int n; cin >> n;
    double rect_area = 0;
    vp dots;
    while (n--) {
      double x, y, w, h, th;
      cin >> x >> y >> w >> h >> th;
      th = th * M_PI / 180;
      rect_area += w * h;
      for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
          point p;
          p.x = x + 0.5 * (i * w * cos(th) + j * h * sin(th));
          p.y = y + 0.5 * (-i * w * sin(th) + j * h * cos(th));
          dots.emplace_back(p);
        }
      }
    }
    vp hull = build_hull(dots);
    printf("%.1f %%\n", round(rect_area * 1000 / area(hull)) / 10);
  }
}
