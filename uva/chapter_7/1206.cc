#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct dot { double x, y; };

struct vec {
  double x, y;
  vec(const dot a, const dot b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

using polygon = vector<dot>;

void print_polygon(const polygon p) {
  bool first = true;
  for (auto d : p) {
    if (!first) printf(" "); first = false;
    printf("(%.3f,%.3f)", d.x, d.y);
  }
  printf("\n");
}

double length2(const vec a) {
  return pow(a.x, 2) + pow(a.y, 2);
}

double cross_product(const vec a, const vec b) {
  return a.x * b.y - a.y * b.x;
}

polygon build_hull(polygon &p) {
  polygon hull;
  size_t k = 0;
  for (size_t i = 1; i < p.size(); i++) {
    if ((p[i].x < p[k].x) ||
        (p[i].x == p[k].x && p[i].y < p[k].y)) k = i;
  }
  swap(p[0], p[k]);
  dot& o = p[0];
  sort(p.begin() + 1, p.end(), [o] (const dot& a, const dot& b) {
    vec va(o, a), vb(o, b);
    if (cross_product(va, vb) == 0) {
      return length2(va) < length2(vb);
    }
    return atan2(va.y, va.x) < atan2(vb.y, vb.x);
  });
  stack<dot> s;
  for (size_t i = 0; i < p.size(); i++) {
    dot &a = p[i];
    while (s.size() > 1) {
      dot &b = s.top(); s.pop();
      dot &c = s.top();
      if (cross_product(vec(c, b), vec(c,a)) > 0) {
        s.push(b);
        break;
      }
    }
    s.push(a);
  }
  if (s.size() > 1) hull.push_back(p[0]);
  while (!s.empty()) {
    hull.push_back(s.top());
    s.pop();
  }
  // reverse(hull.begin(), hull.end());
  // if (hull.size() > 1) hull.emplace_back(hull[0]);
  return hull;
}

int main() {
  string line;
  while (getline(cin, line)) {
    istringstream ss(line);
    string a;
    polygon p;
    while (ss >> a) {
      dot d;
      if (sscanf(a.c_str(),"(%lf,%lf)", &d.x, &d.y)) {
        p.emplace_back(d);
      }
    }
    print_polygon(build_hull(p));
  }
}
