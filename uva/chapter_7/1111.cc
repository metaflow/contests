#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct point {
  int x, y;
};

using vp = vector<point>;

int cross_product(point a, point b, point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool collinear(point a, point b, point c) {
  return cross_product(a, b, c) == 0;
}

double distance(point a, point b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double height(point a, point b, point c) {
  double s = cross_product(a, b, c);
  return abs(s / distance(a, b));
}

void print_polygon(vp p) {
  cout << "{ ";
  for (auto d : p) {
    cout << "(" << d.x << ", " << d.y << "), ";
  }
  cout << " }" << endl;
}

vp convex_hull(vp& polygon) {
  int k = 0;
  for (size_t i = 1; i < polygon.size(); i++) {
    if (polygon[i].x > polygon[k].x) continue;
    if (polygon[i].x == polygon[k].x && polygon[i].y > polygon[k].y) continue;
    k = i;
  }
  swap(polygon[k], polygon[0]);
  auto &o = polygon[0];
  sort(polygon.begin() + 1, polygon.end(),
    [o] (const point& a, const point& b) {
    if (collinear(o, a, b)) {
      return distance(o, a) < distance(o, b);
    }
    int dxa = a.x - o.x;
    int dya = a.y - o.y;
    int dxb = b.x - o.x;
    int dyb = b.y - o.y;
    return atan2(dya, dxa) < atan2(dyb, dxb);
  });
  // print_polygon(polygon);
  stack<point> s;
  s.push(polygon[0]);
  s.push(polygon[1]);
  for (size_t i = 2; i < polygon.size(); i++) {
    auto a = polygon[i];
    while (s.size() > 1) {
      auto b = s.top(); s.pop();
      auto c = s.top();
      if (cross_product(c, b, a) > 0) {
        s.push(b);
        break;
      }
    }
    s.push(a);
  }
  vp hull;
  while (!s.empty()) {
    hull.emplace_back(s.top()); s.pop();
  }
  return hull;
}

int main() {
  int n;
  int tc = 1;
  while (cin >> n, n) {
    printf("Case %d: ", tc++);
    vp polygon;
    while (n--) {
      point p; cin >> p.x >> p.y;
      polygon.emplace_back(p);
    }
    // print_polygon(polygon);
    auto hull = convex_hull(polygon);
    // print_polygon(hull);
    double d = INF;
    for (size_t i = 0; i < hull.size(); i++) {
      int j = (i + 1) % hull.size();
      double m = 0;
      for (size_t k = 0; k < hull.size(); k++) {
        m = max(m, height(hull[i], hull[j], hull[k]));
      }
      d = min(d, m);
    }
    printf("%.2f\n", ceil(d * 100) / 100);
  }
}
