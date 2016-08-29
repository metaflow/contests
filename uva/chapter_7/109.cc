#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct dot { double x, y; };
using polygon = vector<dot>;
using dd = pair<dot, dot>;

double cross_product(dd a, dd b) {
  return (a.second.x - a.first.x) * (b.second.y - b.first.y) -
         (a.second.y - a.first.y) * (b.second.x - b.first.x);
}

double distance(dot a, dot b) {
  return pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5);
}

polygon build_hull(polygon &p) {
  // find left-bottom
  int k = 0;
  for (size_t i = 1; i < p.size(); i++) {
    if (p[i].x > p[k].x) continue;
    // if (p[i].x == p[k].x && p[i].y > p[k].y) continue;
    k = i;
  }
  swap(p[0], p[k]);
  dot &o = p[0];
  sort(p.begin() + 1, p.end(), [o] (const dot& a, const dot& b) {
    if (cross_product(dd{o, a}, dd{o, b}) == 0) {
      return distance(o, a) < distance(o, b);
    }
    return atan2(a.y - o.y, a.x - o.x) < atan2(b.y - o.y, b.x - o.x);
  });
  stack<dot> s;
  s.push(p[0]);
  s.push(p[1]);
  for (size_t i = 2; i < p.size(); i++) {
    dot &a = p[i];
    while (s.size() > 1) {
      dot &b = s.top(); s.pop();
      dot &c = s.top();
      if (cross_product(dd{c, b}, dd{b, a}) > 0) {
        s.push(b);
        break;
      }
    }
    s.push(a);
  }
  polygon hull;
  while (!s.empty()) {
    hull.emplace_back(s.top());
    s.pop();
  }
  return hull;
}

double dot_product(const dd a, const dd b) {
  return (a.second.x - a.first.x) * (b.second.x - b.first.x) +
         (a.second.y - a.first.y) * (b.second.y - b.first.y);
}

double angle(const dot o, const dot a, const dot b) {
  return acos(dot_product(dd{o, a}, dd{o, b}) /
              distance(o, a) /
              distance(o, b));
}

bool inside(polygon &p, dot o) {
  double wind = 0;
  for (size_t i = 0; i < p.size(); i++) {
    size_t j = (i + 1) % p.size();
    if (cross_product(dd{o, p[i]}, dd{o, p[j]}) > 0) {
      wind += angle(o, p[i], p[j]);
    } else {
      wind -= angle(o, p[i], p[j]);
    }
  }
  wind /= 2 * M_PI;
  int n = round(wind);
  // cout << n % 2 << endl;
  return n % 2 != 0;
}

double area(polygon &p) {
  double a = 0;
  for (size_t i = 1; i < p.size() - 1; i++) {
    a += cross_product(dd{p[0], p[i]}, dd{p[0], p[i + 1]});
  }
  return abs(a / 2);
}

int main() {
  vector<polygon> kingdom;
  int n;
  while (cin >> n, n > 0) {
    polygon p;
    while (n--) {
      dot d;
      cin >> d.x >> d.y;
      p.emplace_back(d);
    }
    kingdom.emplace_back(build_hull(p));
  }
  double result = 0;
  vector<bool> used(kingdom.size(), false);
  dot d;
  while (cin >> d.x >> d.y) {
    for (size_t i = 0; i < kingdom.size(); i++) {
      if (used[i]) continue;
      if (inside(kingdom[i], d)) {
        used[i] = true;
        result += area(kingdom[i]);
      }
    }
  }
  printf("%.2f\n", round(result * 100) / 100);
}

