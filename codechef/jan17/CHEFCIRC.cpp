#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <string>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-4;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

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
  point(double x, double y) : x(x), y(y) {}
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
  const bool operator < (const point& o) const {
    if (o.x != x) return x < o.x;
    return y < o.y;
  }
};

ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}

tuple<point, bool> circumscribed_circle(point a, point b, point c) {
  point ac = c - a;
  point ab = b - a;
  point bc = c - b;
  if ((ab * ac < 0) || (ab * bc > 0) || (ac * bc < 0)) {
    return make_tuple(point(), false);
  }
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

l count_covered(vector<point>& v, vl& w, l n, point o, double r) {
  l t = 0;
  for (l i = 0; i < n; i++) if ((v[i] >> (o)) < r + EPS) t += w[i];
  return t;
}

// invariant: answer is within (a, b], f(a) = true, f(b) = true
l binary_search_lower(l a, l b, function<bool(l)> f) {
  while (b - a > 1) {
    l m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

pair<point, double> find_best_in(vector<point>& v, vl& w, l m, l i, vector<pair<double, point>>& oo) {
  if (oo.empty()) return make_pair(point(), e9);
  l n = v.size();
  sort(oo.begin(), oo.end());
  point& a = v[i];
  // try most distant
  point o = oo[oo.size() - 1].second;
  l c = count_covered(v, w, n, o, a >> o);
  if (c < m) return make_pair(point(), e9);
  // invoke binary search
  l lb = binary_search_lower(0, oo.size() - 1, [&](l x) -> bool {
    return (count_covered(v, w, n, oo[x].second, a >> oo[x].second)) >= m;
  });
  return make_pair(oo[lb].second, a >> oo[lb].second);
}

pair<point, double> solve(vector<point>& v, l m) {
  l n = v.size();
  vl w(n, 1);
  vector<point> u;
  vl y;
  // merge points
  for (l i = 0; i < n; i++) {
    if (w[i] == 0) continue;
    for (l j = i + 1; j < n; j++) {
      if ((v[i] >> v[j]) < EPS) {
        w[i] += w[j];
        w[j] = 0;
      }
    }
    u.emplace_back(v[i]);
    y.emplace_back(w[i]);
  }
  swap(y, w);
  swap(v, u);
  n = v.size();
  double best_r = e9;
  point best_o(0, 0);
  for (auto i : w) {
    if (i >= m) {
      best_r = EPS;
      best_o = v[i];
      break;
    }
  }
  // try to find segment
  for (l i = 0; i < n; i++) {
    for (l j = i + 1; j < n; j++) {
      point o = (v[i] + v[j]) * 0.5;
      double r = v[i] >> o;
      if (r >= best_r) continue;
      if (count_covered(v, w, n, o, r) >= m) {
        best_r = r;
        best_o = o;
      }
    }
  }
  // triangles
  for (l i = 0; i < n; i++) {
    for (l j = i + 1; j < n; j++) {
      if ((v[i] >> v[j]) >= 4 * best_r) continue;
      vector<pair<double, point>> positive, negative;
      for (l k = j + 1; k < n; k++) {
        point o;
        bool ok;
        tie(o, ok) = circumscribed_circle(v[i], v[j], v[k]);
        if (!ok) continue;
        double r = v[i] >> o;
        if (r >= best_r) continue;
        positive.emplace_back(v[i] >> o, o);
      }
      sort(positive.begin(), positive.end());
      for (auto p : positive) {
        if (p.first > best_r) break;
        if (count_covered(v, w, n, p.second, p.first) >= m) {
          tie(best_r, best_o) = p;
        }
      }
    }
  }
  return make_pair(best_o, best_r);
}

pair<point, double> brute(vector<point> v, l m) {
  vl w(v.size(), 1);
  for (double r = EPS; r < 10; r += 0.1) {
    for (double x = -10; x < 10; x += 0.1) {
      for (double y = -10; y < 10; y += 0.1) {
        if (count_covered(v, w, v.size(), point(x, y), r * r) >= m) return make_pair(point(x, y), r * r);
      }
    }
  }
  return make_pair(point(0, 0), e9);
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

bool check() {
  for (l tt = 0; tt < 200; tt++) {
    LOG << '.';
    l n = random_in_range(1, 20);
    l m = random_in_range(1, n);
    vector<point> v(n);
    for (l i = 0; i < n; i++) {
      v[i].x = random_in_range(-5, 5);
      v[i].y = random_in_range(-5, 5);
    }
    point o;
    double r;
    tie(o, r) = solve(v, m);
    auto b = brute(v, m);
    if (b.second + EPS < r) {
      LOG << endl;
      LOG << "brute is better" << endl;
      for (auto p : v) {
        LOG << p << " ";
      }
      LOG << endl << "m " << m << endl;
      LOG << "normal " << o << " " << r << endl;
      LOG << "brute " << b.first << " " << b.second << endl;
      return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // vector<future<bool>> a;
  // for (int i = 0; i < 8; i++) a.emplace_back(async(&check));
  // bool ok = true;
  // for (auto& x : a) ok = ok && x.get();
  // if (ok) LOG << "OK" << endl;
  // return 0;
  l n, m;
  cout.precision(6);
  while (cin >> n >> m) {
    vector<point> v(n);
    for (l i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    point o;
    double r;
    tie(o, r) = solve(v, m);
    cout << fixed << sqrt(r) << endl;
  }
}
