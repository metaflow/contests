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
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
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
const l      INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l      e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream& in, ostream& out);
int  main(int argc, char** argv) {
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
const l MOD = e9 + 7;  // end of template

struct point {
  l x, y;
  point() {}
  point(l _x, l _y) : x(_x), y(_y) {}
  // scalar multiplication
  l     operator*(const point& o) { return x * o.x + y * o.y; }
  point operator*(const l m) { return point(x * m, y * m); }
  // vector multiplication
  l     operator^(const point& o) { return x * o.y - y * o.x; }
  point operator-(const point& o) { return point(x - o.x, y - o.y); }
  point operator+(const point& o) { return point(x + o.x, y + o.y); }
  // squared distance
  l operator>>(const point& o) {
    point d = (*this - o);
    return d * d;
  }
  double distance(const point& o) { return sqrt(*this >> o); }
  bool   equal(l a, l b) const {
    if (abs(a - b) < EPS) return true;
    // Is x or y too close to zero?
    if (abs(a) < EPS || abs(b) < EPS) return false;
    // Check relative precision.
    return (abs((a - b) / a) < EPS) && (abs((a - b) / b) < EPS);
  }
  bool operator<(const point& o) const {
    if (o.x != x) return x < o.x;
    if (not equal(o.x, x)) return x < o.x;
    return y < o.y;
  }
};

// 0 - no intersection, 1 - point o1, 2 - segment [o1, o2]
l segment_intersection(point a, point b, point c, point d, point& o1,
                       point& o2) {
  point  x = c - a, y = d - a, z = b - a;
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
ostream& operator<<(ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}
using vp = vector<point>;

// [1, n]
struct BIT {
  vl tree;
  l max_p;
  BIT(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  l get(l p) {  // sum of [1, p], O(log(max))
    l sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  l get(l from, l to) {  // [from, to]
    return get(to) - get(from - 1);
  }
  // O(log(max))
  void add(l p, l value) {
    while (p <= max_p) {
      tree[p] += value;
      p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  l find(l sum) {
    l mask = max_p;
    while (true) {
      l lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    l p = 0;
    l top = -1;
    while (mask != 0) {
      l m = p + mask;
      if (m <= max_p) {
        if (sum == tree[m]) top = m;
        if (sum > tree[m]) {
          p = m;
          sum -= tree[m];
        }
      }
      mask >>= 1;
    }
    if (sum != 0) return top;
    return p;
  }
};


void solve(istream& in, ostream& out) {
  l n;
  in >> n;
  l k;
  in >> k;
  vp vv(n);
  F(i, 0, n) in >> vv[i].x >> vv[i].y;
  vp uu(n);
  F(i, 0, n) {
    uu[i].x = vv[i].x + vv[i].y;
    uu[i].y = vv[i].x - vv[i].y;
  }
  vl ti(n);
  iota(all(ti), 0);
  sort(all(ti), [&](l a, l b) { return vv[a].x < vv[b].x; });
  set<ll> right;
  F(i, 0, n) right.emplace(uu[i].x, i);
  priority_queue<l, vl, greater<l>> q;
  l                                 rc = 0;
  l                                 sr = 0, sl = 0;
  l                                 z = INF;
  auto ir = right.begin();
  F(i, 0, n) {
    l p = ti[i];
    l x = vv[p].x;
    while (ir != right.end() && rc + q.size() < k) {
      sr += ir->first;
      ir++;
      rc++;
    }
    while (not q.empty() and ir != right.end()) {
      if (x - q.top() <= ir->first - x) break;
      sl -= q.top();
      q.pop();
      sr += ir->first;
      ir++;
      rc++;
    }
    C(q.size() + rc == k, q.size(), rc, k);
    z = min(z, x * l(q.size()) - sl + sr - x * rc);
    q.emplace(uu[p].y);
    auto it = right.find(make_pair(uu[p].x, p));
    if (it == right.end()) continue;
    if (ir != right.end()) {
    } else {
    }
    if (it* < *ir)
    left[p] = true;
    if (p < xip) {
      xic--;
      sr -= uu[p].x;
    }
  }
  out << z << lf;
}
