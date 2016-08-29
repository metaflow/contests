#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct dot { int x, y; };

using dd = pair<dot, dot>;

int dot_product(const dd a, const dd b) {
  return (a.second.x - a.first.x) * (b.second.x - b.first.x) +
         (a.second.y - a.first.y) * (b.second.y - b.first.y);
}

ll cross_product(const dd a, const dd b) {
  return (a.second.x - a.first.x) * (b.second.y - b.first.y) -
         (a.second.y - a.first.y) * (b.second.x - b.first.x);
}

void print_polygon(vector<dot> &p) {
  printf("{");
  for (auto d : p) {
    printf("(%d, %d) ", d.x, d.y);
  }
  printf("}");
}

ll distance(const dot a, const dot b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool inside(vector<dot>& p, dot a) {
  if (p.size() == 1) {
    return distance(p[0], a) == 0;
  }
  if (p.size() == 2) {
    return cross_product(dd{p[0], a}, dd{p[0], p[1]}) == 0 &&
           dot_product(dd{p[0], a}, dd{p[0], p[1]}) >= 0 &&
           distance(p[0], a) <= distance(p[0], p[1]);
  }
  ll last = 0;
  for (size_t i = 0; i < p.size(); i++) {
    auto j = (i + 1) % p.size();
    ll q = cross_product(dd{p[i], a}, dd{p[i], p[j]});
    if (last * q < 0) return false;
    if (q != 0) last = q;
  }
  return true;
}

vector<dot> build_hull(vector<dot>& p) {
  vector<dot> hull;
  if (p.size() < 3) return hull;
  size_t k = 0;
  for (size_t i = 1; i < p.size(); i++) {
    if ((p[i].x < p[k].x)) k = i;
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
  for (size_t i = 0; i < p.size(); i++) {
    dot &a = p[i];
    while (s.size() > 1) {
      dot &b = s.top(); s.pop();
      dot &c = s.top();
      if (cross_product(dd{c, b}, dd{c, a}) > 0) {
        s.push(b);
        break;
      }
    }
    s.push(a);
  }
  while (!s.empty()) {
    hull.emplace_back(s.top());
    s.pop();
  }
  return hull;
}

int main() {
  int c, r, o;
  int tc = 0;
  while (cin >> c >> r >> o, c + r + o) {
    printf("Data set %d:\n", ++tc);
    vector<dot> cops(c), robbers(r);
    while (c--) cin >> cops[c].x >> cops[c].y;
    while (r--) cin >> robbers[r].x >> robbers[r].y;
    auto cops_hull = build_hull(cops);
    auto robbers_hull = build_hull(robbers);
    // cout << cops_hull.size() << " ch\n";
    // print_polygon(cops_hull);
    while (o--) {
      dot other;
      cin >> other.x >> other.y;
      string status = "neither";
      if (cops.size() > 2 && inside(cops_hull, other)) {
        status = "safe";
      } else if (robbers.size() > 2 && inside(robbers_hull, other)) {
        status = "robbed";
      }
      printf("     Citizen at (%d,%d) is %s.\n",
        other.x, other.y, status.c_str());
    }
    printf("\n");
  }
}


