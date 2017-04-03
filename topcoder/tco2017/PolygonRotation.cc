#include <bits/stdc++.h>

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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

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
    if (abs(o.x - x) < EPS) return x < o.x;
    return y < o.y;
  }
};

ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}

// 0 - no intersection, 1 - point o1, 2 - segment [o1, o2]
l segment_intersection(point a, point b, point c, point d, point& o1, point &o2) {
  point x = c - a, y = d - a, z = b - a;
  double t = (x ^ z) + (z ^ y);
  if (abs(t) < EPS) {
    if (abs(x ^ y) < EPS) {
      vector<point> v = {a, b, c, d};
      sort(ALL(v));
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

bool equal_double(double x, double y, double epsilon) {
  if (abs(x - y) < epsilon) return true;
  // Is x or y too close to zero?
  if (abs(x) < epsilon || abs(y) < epsilon) return false;
  // Check relative precision.
  return (abs((x - y) / x) < epsilon) && (abs((x - y) / y) < epsilon);
}

bool ge(double x, double y) {
  return (x > y) or equal_double(x, y, EPS);
}

class PolygonRotation {
public:
  double volume(point a, point b) {
    // LOG << "+ " << a << ".." << b << '\n';
    double r1 = a.x, r2 = b.x;
    if (r1 > r2) swap(r1, r2);
    double h = abs(a.y - b.y);
    if (r2 - r1 < EPS) return PI * r1 * r1 * h;
    double t = r2 * h / (r2 - r1);
    return PI / 3 * (r2 * r2 * t - (t - h) * r1 * r1);
  }

  double findx(vector<point>& a, double y) {
    F(i, 1, a.size()) {
      if (ge(a[i-1].y, y) and ge(y, a[i].y)) {
        if (equal_double(a[i].y, a[i-1].y, EPS)) {
          return max(a[i].x, a[i-1].x);
        }
        return a[i].x + (a[i-1].x - a[i].x) / (a[i].y - a[i-1].y) * (a[i].y - y);
      }
    }
    assert(false);
    return 0;
  }

  double getVolume(vector<int> X, vector<int> Y) {
    l n = X.size();
    vector<point> a, b;
    double result = 0;
    set<double> ys;
    bool next = false;
    a.emplace_back(point(X[0], Y[0]));
    F(i, 1, n) {
      if (not next) a.emplace_back(point(X[i], Y[i]));
      if (X[i] == 0) {
        next = true;
      }
      if (next) b.emplace_back(point(-X[i], Y[i]));
    }
    b.emplace_back(point(X[0], Y[0]));
    reverse(ALL(b));
    F(i, 0, a.size()) ys.emplace(a[i].y);
    F(i, 0, b.size()) ys.emplace(b[i].y);
    F(i, 1, a.size()) F(j, 1, b.size()) {
      point c, d;
      if (segment_intersection(a[i], a[i-1], b[j], b[j-1], c, d) == 1) {
        ys.emplace(c.y);
      }
    }
    point u = a.back();
    for (auto y : ys) {
      double x = max(findx(a, y), findx(b, y));
      point w(x, y);
      result += volume(u , w);
      swap(w, u);
    }
    return result;
  }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (equal_double(Expected, Received, 1e-10)) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.141592653589793; verify_case(0, Arg2, getVolume(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 1, 0, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 1, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.0943951023931953; verify_case(1, Arg2, getVolume(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 3, 0, -2, -2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 0, -3, -1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 49.91641660703782; verify_case(2, Arg2, getVolume(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 3, 3, 0, -1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, -2, -2, -1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 113.09733552923255; verify_case(3, Arg2, getVolume(Arg0, Arg1)); }

// END CUT HERE
;
};

// BEGIN CUT HERE
int main() {
  PolygonRotation ___test;
  ___test.run_test(-1);
}
// END CUT HERE
