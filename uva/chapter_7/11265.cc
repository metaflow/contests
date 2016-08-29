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

using vec = pair<point, point>;
using polygon = vector<point>;

double dot_product(const point o, const point a, const point b) {
  return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

double cross_product(const point o, const point a, const point b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double cross_product(vec a, vec b) {
  return (a.second.x - a.first.x) * (b.second.y - b.first.y)
       - (a.second.y - a.first.y) * (b.second.x - b.first.x);
}

point intersect(point a, point b, point c, point d) {
  double k = abs(cross_product(vec{a, b}, vec{a, c}) /
             cross_product(vec{a, b}, vec{c, d}));
  return point{c.x + k * (d.x - c.x), c.y + k * (d.y - c.y)};
}

double area(polygon &p) {
  auto &o = p[0];
  double a = 0;
  for (int i = 2; i < p.size(); i++) {
    a += cross_product(vec{o, p[i - 1]}, vec{o, p[i]});
  }
  return abs(a) / 2;
}

void print_point(point d) {
  cout << "( " << d.x << ", " << d.y << ") ";
}

void print_polygon(polygon &p) {
  cout << "{ ";
  for (auto d : p) {
    print_point(d);
  }
  cout << "}\n" ;
}

int main() {
  int tc = 0;
  double w, h;
  point o;
  int n;
  while (cin >> n) {
    printf("Case #%d: ", ++tc);
    cin >> w >> h >> o.x >> o.y;
    vector<vec> lines;
    while (n--) {
      vec line;
      cin >> line.first.x >> line.first.y >> line.second.x >> line.second.y;
      lines.emplace_back(line);
    }
    polygon p;
    p.emplace_back(point{0, 0});
    p.emplace_back(point{w, 0});
    p.emplace_back(point{w, h});
    p.emplace_back(point{0, h});
    // print_polygon(p);
    for (auto v : lines) {
      polygon k;
      double o_sign = cross_product(vec{v.first, v.second}, vec{v.first, o});
      double last_sign = o_sign;
      int from = 0;
      for (; from < p.size(); from++) {
        double t = cross_product(vec{v.first, v.second},
                                 vec{v.first, p[from]});
        if (t * o_sign > 0) break;
      }
      // cout << "from " << from << " " << o_sign << endl;
      // k.emplace_back(p[from]);
      for (int i = from + 1; i < from + 1 + p.size(); i++) {
        auto a = p[(i - 1) % p.size()];
        auto b = p[i % p.size()];
        double w = cross_product(vec{v.first, v.second},
                                 vec{v.first, b});
        // cout << "checking "; print_point(b);
        // cout << " " << w << endl;
        if (w * last_sign < 0) {
          k.emplace_back(intersect(a, b, v.first, v.second));
          // cout << "X "; print_point(k.back()); cout << endl;
        }
        last_sign = w;
        if (w * o_sign < 0) continue;
        k.emplace_back(b);
      }
      swap(p, k);
      // print_polygon(p);
    }
    printf("%.3f\n", area(p));
  }
}
