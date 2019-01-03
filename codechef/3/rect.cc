#if defined(LOCAL)
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#endif
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using ii = pair<int, int>;
using lu = unsigned long long;
using l = long long;
using vs = vector<string>;
using vii = vector<ii>;
using vl = vector<l>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using ll = pair<l, l>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream &in, ostream &out);
int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7; // end of template

struct point {
  l x, y;
  point() {}
  point(l _x, l _y) : x(_x), y(_y) {}
  // scalar multiplication
  l operator * (const point & o) {
    return x * o.x + y * o.y;
  }
  point operator * (const l m) {
    return point(x * m, y * m);
  }
  // vector multiplication
  l operator ^ (const point & o) {
    return x * o.y - y * o.x;
  }
  point operator - (const point& o) {
    return point(x - o.x, y - o.y);
  }
  point operator + (const point& o) {
    return point(x + o.x, y + o.y);
  }
  // squared distance
  l operator >> (const point& o) {
    point d = (*this - o);
    return d * d;
  }
  double distance(const point& o) {
    return sqrt(*this >> o);
  }
  bool equal(l a, l b) const {
    if (abs(a - b) < EPS) return true;
    // Is x or y too close to zero?
    if (abs(a) < EPS || abs(b) < EPS) return false;
    // Check relative precision.
    return (abs((a - b) / a) < EPS) && (abs((a - b) / b) < EPS);
  }
  bool operator < (const point& o) const {
    if (o.x != x) return x < o.x;
    if (not equal(o.x, x)) return x < o.x;
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
using vp = vector<point>;
using rect = pair<point, point>; // TODO: operations with rectangles.

l area(const rect& r) {
  return (r.second.x - r.first.x) * (r.second.y - r.first.y);
}

rect intersect(rect a, rect b) {
  rect z;
  rect o;
  point& q = z.first;
  point& p = z.second;
  q.x = max(a.first.x, b.first.x);
  q.y = max(a.first.y, b.first.y);
  p.x = min(a.second.x, b.second.x);
  p.y = min(a.second.y, b.second.y);
  if (q.x >= p.x) return o;
  if (q.y >= p.y) return o;
  return z;
}

bool f(l p, l n, vp& corners, vp& pp, vl& cc, l m) {
  if (p == n) {
    l z = 0;
    vector<rect> rr(n);
    F(i, 0, n) {
      auto &a = rr[i].first;
      auto &b = rr[i].second;
      a = pp[i];
      b = corners[cc[i]];
      if (a.x > b.x) swap(a.x, b.x);
      if (a.y > b.y) swap(a.y, b.y);
    }
    F(i, 0, n) z += area(rr[i]);
    F(i, 0, n) F(j, i + 1, n) z -= area(intersect(rr[i], rr[j]));
    if (n == 3) z += area(intersect(rr[0], intersect(rr[1], rr[2])));
    return z == (m - 1) * (m - 1);
  }
  F(i, 0, 4) {
    cc[p] = i;
    if (f(p + 1, n, corners, pp, cc, m)) return true;
  }
  return false;
}

void solve(istream &in, ostream &out) {
  l tcc; in >> tcc;
  while (tcc--) {
    l n, m; in >> n >> m;
    vp pp(n); F(i, 0, n) in >> pp[i].x >> pp[i].y;
    if (n >= 4) {
      out << "yes" << lf;
      continue;
    }
    vp corners = {point(0,0), point(m - 1, 0), point(0, m - 1), point(m - 1, m - 1)};
    vl cc(n);
    if (f(0, n, corners, pp, cc, m)) {
      cout << "yes" << lf;
    } else {
      cout << "no" << lf;
    }
  }
}
