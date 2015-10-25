#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

struct point {
  double x, y;
  point() {}
  point(double x, double y) : x(x), y(y) {}
  // scalar multiplication
  double operator * (const point & o) {
    return x * o.x + y * o.y;
  }
    // scalar multiplication
  point operator * (const double & o) {
    return point(x * o, y * o);
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
  // distance between points
  double operator >> (const point& o) {
    point d = (*this - o);
    return sqrt(d * d);
  }
  const bool operator < (const point& o) const {
    if (o.x != x) return x < o.x;
    return y < o.y;
  }
};

ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}

point after(point a, point v, double s, point w, double t) {
  point o(0, 0);
  double n = s / (v >> o);
  return a + (w * t) + (v * n) * t;
}

bool equal_double(double x, double y, double epsilon) {
  if (abs(x - y) < epsilon) return true;
  // Is x or y too close to zero?
  if (abs(x) < epsilon || abs(y) < epsilon) return false;
  // Check relative precision.
  return (abs((x - y) / x) < epsilon) && (abs((x - y) / y) < epsilon);
}

// invariant: answer is within (a, b], f(a) = false, f(b) = true
double binary_search_lower(double a, double b, function<bool(double)> f) {
  while (!equal_double(a, b, EPS)) {
    double  m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

double time_to(point a, point b, double s, point w) {
  return binary_search_lower(0, 10000000, [&] (double x) {
    point q = a + (w * x);
    return (b >> q) / s < x;
  });
}

double with_switch(point a, point b, point d, double q, point w1, point w2, double change, double v) {
  point k(d.x * cos(q) - d.y * sin(q), d.x * sin(q) + d.y * cos(q));
  point kk = after(a, k, v, w1, change);
  return change + time_to(kk, b, v, w2);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  point a, b;
  while (cin >> a.x >> a.y >> b.x >> b.y) {
    double change, v;
    cin >> v >> change;
    point w1, w2;
    cin >> w1.x >> w1.y;
    cin >> w2.x >> w2.y;
    auto t = time_to(a, b, v, w1);
    cout << fixed << setprecision(10);
    if (t < change) {
      cout << t << endl;
    } else {
      point d = b - a;
      double f = -M_PI / 2;
      double t = M_PI / 2;
      while (!equal_double(f, t, EPS)) {
        double q = (2 * f + t) / 3;
        double r = (f + 2 * t) / 3;
        double tq = with_switch(a, b, d, q, w1, w2, change, v);
        double tr = with_switch(a, b, d, r, w1, w2, change, v);
        if (tq > tr) f = q; else t = r;
        // cerr << f << " " << t << endl;
        // cerr << tq << " " << tr << endl;
      }
      cout << with_switch(a, b, d, f, w1, w2, change, v) << endl;
    }
  }
}
