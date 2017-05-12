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
const double EPS = 1e-16; static constexpr auto PI = acos(-1);
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
      sort(all(v));
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
l sign(double n) {
  if (n < 0) return -1;
  if (n == 0) return 0;
  return 1;
}

l cong(l x, l mod) {
  return (x % mod + mod) % mod;
}

// (a * b) % mod, safe for l near max
l mult_mod(l a, l b, l mod) {
  l x = 0;
  while (b) {
    if (b % 2) x = (x + a) % mod;
    a = (a * 2) % mod;
    b /= 2;
  }
  return x;
}

// (base^power) % mod, safe for l near max
l pow_mod(l base, l power, l mod) {
  l r = 1;
  while (power) {
    if (power % 2) r = mult_mod(r, base, mod);
    base = mult_mod(base, base, mod);
    power /= 2;
  }
  return r;
}

l divup(l a, l b) { // ceil div
  return (a + b - 1) / b;
}

// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
l extended_euclid(l a, l b, l& x, l& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  l d = extended_euclid(b, a % b, x, y);
  l t = y;
  y = x - (a / b) * y;
  x = t;
  return d;
}

// return b: a * b = 1 (mod n)
l inverse_mod(l a, l n) {
  l x, y;
  l d = extended_euclid(a, n, x, y);
  if (d != 1) return 0;
  return cong(x, n);
}

l nCr(l n, l k, l mod) {
  l a = 1;
  for (l i = n; i > n - k; i--) a = mult_mod(a, i, mod);
  l b = 1;
  F(i, 1, k + 1) b = mult_mod(b, i, mod);
  b = inverse_mod(b, mod);
  return mult_mod(a, b, mod);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n_red, n_blue;
  while (cin >> n_red >> n_blue) {
    // LOG << "-----------" << lf;
    bool inf = n_blue < 2;
    vector<point> red(n_red), blue(n_blue);
    F(i, 0, n_red) cin >> red[i].x >> red[i].y;
    F(i, 0, n_blue) cin >> blue[i].x >> blue[i].y;
    vl hull = convex_hull(blue);
    l h = hull.size();
    F(i, 0, h) {
      auto a = blue[hull[i]];
      auto b = blue[hull[(i + 1) % h]];
      for (auto r : red) {
        if (((b - a) ^ (r - a)) <= 0.0) {
          // LOG << "INF normal hull" << endl;
          inf = true;
          break;
        }
      }
    }
    double answer = 0;
    F(i, 0, n_blue) {
      vector<point> iblue, ired;
      point o = blue[i];
      iblue.emplace_back(point(0,0));
      F(j, 0, n_blue) {
        if (j == i) continue;
        iblue.emplace_back((blue[j] - o) * (1.0 / (blue[j] >> o)));
      }
      for (auto r : red) ired.emplace_back((r - o) * (1.0 / (r >> o)));
      auto ihull = convex_hull(iblue);
      // LOG << "iblue" << iblue << " ired " << ired << ' ' << ihull << endl;
      l ih = ihull.size();
      F(j, 0, ih) {
        auto a = iblue[ihull[j]];
        auto b = iblue[ihull[(j + 1) % ih]];
        for (auto r : ired) {
          if (((b - a) ^ (r - a)) <= 0.0) {
            auto d = abs((b ^ a) / a.distance(b));
            // LOG << d << endl;
            if (d < EPS) {
              // LOG << "INF ihull " << i << ' ' << j << ' ' << d << endl;
              inf = true;
            } else {
              answer = max(answer, 1.0 / d);
            }
            break;
          }
        }
      }
      F(j, 0, ih) {
        auto a = iblue[ihull[j]];
        auto b = iblue[ihull[(j + 1) % ih]];
        auto c = iblue[ihull[(j - 1 + ih) % ih]];
        for (auto r : ired) {
          if (((r - a) ^ (b - a)) * ((r - a) ^ (c - a)) >= 0.0) {
            auto d = abs((a ^ r) / a.distance(r));
            // LOG << d << endl;
            if (d < EPS) {
              // LOG << "INF ihull " << i << ' '  << j << ' ' << d << endl;
              inf = true;
            } else {
              answer = max(answer, 1.0 / d);
            }
          }
        }
      }
    }
    if (inf) {
      cout << -1 << lf;
    } else {
      cout << fixed << setprecision(9) << answer / 2 << lf;
    }
  }
}
