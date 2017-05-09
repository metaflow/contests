#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

// TODO:
double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

bool equal_double(double x, double y) {
  if (abs(x - y) < EPS) return true;
  // Is x or y too close to zero?
  if (abs(x) < EPS || abs(y) < EPS) return false;
  // Check relative precision.
  return (abs((x - y) / x) < EPS) && (abs((x - y) / y) < EPS);
}

struct point {
  double x, y;
  point() {}
  point(double _x, double _y) : x(_x), y(_y) {}
  // scalar multiplication
  double operator * (const point & o) {
    return x * o.x + y * o.y;
  }
  point operator * (const double m) {
    return point(x * m, y * m);
  }
  // vector multiplication
  double operator ^ (const point & o) {
    return x * o.y - y * o.x;
  }
  point operator - (const point& o) {
    return point(x - o.x, y - o.y);
  }
  point operator + (const point& o) {
    return point(x + o.x, y + o.y);
  }
  // squared distance
  double operator >> (const point& o) {
    point d = (*this - o);
    return d * d;
  }
  double distance(const point& o) {
    return sqrt(*this >> o);
  }
  bool operator < (const point& o) const {
    if (o.x != x) return x < o.x;
    if (not equal_double(o.x, x)) return x < o.x;
    return y < o.y;
  }
};

// 0 - no intersection, 1 - point o1, 2 - segment [o1, o2]
l segment_intersection(point a, point b, point c, point d, point& o1, point &o2) {
  point x = c - a, y = d - a, z = b - a;
  double t = (x ^ z) + (z ^ y);
  if (abs(t) < EPS) {
    if (abs(x ^ y) < EPS) {
      vector<point> v = {a, b, c, d};
      sort(all(v)); // TODO
      o1 = v[1];
      o2 = v[2];
      return 2;
    } else {
      return 0;
    }
  }
  t = (x ^ y) / t;
  if (t < 0 or t > 1) return 0;
  o1 = o2 = a + z * t;
  return 1;
}
ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}

// indexes of points of convex hull, ccw from bottom left point
vl convex_hull(vector<point>& p) {
  vl hull;
  l a = 0;
  l n = p.size();
  if (n < 2) return hull;
  F(i, 1, n) {
    if (p[i].y < p[a].y or (equal_double(p[i].y, p[a].y) and p[i].x < p[a].x)) {
      a = i;
    }
  }
  vector<tuple<double, point, l>> ang;
  F(i, 0, n) if (i != a) {
    ang.emplace_back(make_tuple(atan2(p[i].y - p[a].y, p[i].x - p[a].x), p[i], i));
  }
  sort(all(ang));
  hull.emplace_back(a);
  l b = get<2>(ang[0]);
  hull.emplace_back(b);
  F(i, 1, n - 1) {
    l c = get<2>(ang[i]);
    double r = (p[b] - p[a]) ^ (p[c] - p[b]);
    while (not equal_double(r, 0) and r < 0) {
      hull.pop_back();
      b = a;
      assert(hull.size() >= 2);
      a = hull[hull.size() - 2];
      r = (p[b] - p[a]) ^ (p[c] - p[b]);
    }
    if (equal_double(r, 0)) {
      if ((p[b] - p[a]) * (p[c] - p[b]) > 0) {
        b = c;
        hull.pop_back();
        hull.emplace_back(c);
      }
    } else {
      a = b;
      b = c;
      hull.emplace_back(c);
    }
  }
  return hull;
}

bool is_convex_hull(vector<point>& ps, vl& hull) {
  if (hull.size() < 2) return false;
  l n = hull.size();
  F(i, 0, n) {
    l j = (i + 1) % n;
    point v = ps[hull[j]] - ps[hull[i]];
    l sign = 0;
    for (auto p : ps) {
      point u = p - ps[hull[i]];
      double m = u ^ v;
      if (equal_double(0, m)) continue;
      l t = (m < 0) ? -1 : 1;
      if (sign != 0 and sign != t) return false;
      sign = t;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  F(size, 4, 10) {
    F(tc, 0, 10000) {
      vector<point> ps(size);
      F(i, 0, size) {
        bool f = true;
        while (f) {
          ps[i].x = random_in_range(0, 10); // random_double() * 10;
          ps[i].y = random_in_range(0, 10); // random_double() * 10;
          f = false;
          F(j, 0, i)
            f = f or (equal_double(ps[i].x, ps[j].x) and
                      equal_double(ps[i].y, ps[j].y));
        }
      }
      auto hull = convex_hull(ps);
      if (not is_convex_hull(ps, hull)) {
        cout << ps << endl;
        // cout << hull << endl;
        vector<point> h;
        for (auto i : hull) {
          h.emplace_back(ps[i]);
        }
        cout << h << endl;
        return 1;
      }
    }
  }
  cout << "PASSED" << endl;
  return 0;
}
