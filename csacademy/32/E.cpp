#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "E"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

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

class Affine {
  vvd M = {{1,0,0}, {0,1,0}, {0, 0, 1}};
  vvd _m(vvd a, vvd b) {
    l n = a.size();
    l k = b.size();
    l m = b[0].size();
    vvd c(n);
    for (l i = 0; i < n; i++) c[i].resize(m);
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < m; j++) {
        for (l q = 0; q < k; q++) {
          c[i][j] = (c[i][j] + a[i][q] * b[q][j]);
        }
      }
    }
    return c;
  }
public:
  void translate(point d) { M = _m({{1, 0, d.x}, {0, 1, d.y}, {0, 0, 1}}, M); }
  // clockwise, rads
  void rotate(double a) {
    M = _m({{cos(a),sin(a),0}, {-sin(a),cos(a),0}, {0, 0, 1}}, M);
  }
  void scale(point d) { M = _m({{d.x, 0, 0}, {0, d.y, 0}, {0, 0, 1}}, M); }
  void shearX(double a) { M = _m({{1, tan(a), 0}, {0, 1, 0}, {0, 0, 1}}, M); }
  void shearY(double a) { M = _m({{1, 0, 0}, {tan(a), 1, 0}, {0, 0, 1}}, M); }
  point apply(point p) {
    auto r = _m(M, {{p.x}, {p.y}, {1}});
    return point(r[0][0], r[1][0]);
  }

  void reset() { M = {{1,0,0}, {0,1,0}, {0, 0, 1}}; }
};


void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    point p(1,0);
    vector<point> answer;
    answer.emplace_back(0, 0);
    double a = PI / 3 / (n - 2);
    F(i, 0, n - 1) {
      Affine transform;
      transform.rotate(a * i);
      answer.emplace_back(transform.apply(p));
    }
    for (auto r : answer) {
      cout << r.x << ' ' << r.y << lf;
    }
#if defined(LOCAL)
    l test = n;
    F(i, 0, n) {
      F(j, 0, i) {
        double d = answer[i] >> answer[j];
        if (equal_double(d, 1)) {
          test--;
        } else {
          assert(d < 1);
          assert(d >= 0.0000001);
        }
      }
    }
    debug(test);
    assert(test == 0);
#endif
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
