#define ONLINE_JUDGE
#include <bits/stdc++.h>
#if !defined(ONLINE_JUDGE)
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

#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
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

tuple<point, bool> circumscribed_circle(point a, point b, point c) {
  point ac = c - a;
  point ab = b - a;
  point bc = c - b;
  // if ((ab * ac < 0) || (ab * bc > 0) || (ac * bc < 0)) {
    // return make_tuple(point(), false);
  // }
  if (abs(ab ^ ac) < 1e-8) { // line
    return make_tuple(point(), false);
  }
  point x(ac.y, -ac.x);
  point y(ab.y, -ab.x);
  point e = a + (ac * 0.5);
  point d = a + (ab * 0.5);
  point z = d - e;
  double w = - (x ^ z) / (x ^ y);
  point o = d + (y * w);
  return make_tuple(o, true);
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l w;
  while (cin >> w) {
    vector<point> ws, rs;
    F(i, 0, w) { point a; cin >> a.x >> a.y; ws.emplace_back(a); }
    l r; cin >> r;
    F(i, 0, r) { point a; cin >> a.x >> a.y; rs.emplace_back(a); }
    l answer = 0;
    F(i, 0, w) F(j, i + 1, w) F(k, j + 1, w) {
      auto c = circumscribed_circle(ws[i], ws[j], ws[k]);
      if (not get<1>(c)) continue;
      auto o = get<0>(c);
      auto r2 = o >> ws[i];
      l t = 0;
      F(m, 0, r) if (r2 > (o >> rs[m])) t++;
      answer = max(answer, t);
    }
    cout << answer << lf;
  }
}
