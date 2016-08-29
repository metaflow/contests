#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct point {
  double x, y, z;
  point() {}
  point(double x, double y, double z) : x(x), y(y), z(z) {}
  // scalar multiplication
  double operator * (const point & o) {
    return x * o.x + y * o.y + z * o.z;
  }
  // vector multiplication
  point operator ^ (const point & o) {
    return point(y * o.z - z * o.y,
                -x * o.z + z * o.x,
                 y * o.x - x * o.y);
  }
  point operator - (const point& o) {
    return point(x - o.x, y - o.y, z - o.z);
  }
  point operator + (const point& o) {
    return point(x + o.x, y + o.y, z + o.z);
  }
  // distance between points
  double operator >> (const point& o) {
    point d = (*this - o);
    return sqrt(d * d);
  }
};

point polar_to_point(double r, double la, double lo) {
  return point(r * cos(la) * cos(lo), r * cos(la) * sin(lo), r * sin(la));
}

ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ", " << p.z << ")";
  return s;
}

bool equal_double(double x, double y, double epsilon) {
  if (abs(x - y) < epsilon) return true;
  // Is x or y too close to zero?
  if (abs(x) < epsilon || abs(y) < epsilon) return false;
  // Check relative precision.
  return (abs((x - y) / x) < epsilon) && (abs((x - y) / y) < epsilon);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vector<pair<double, double>> airports(n);
    vector<point> p(n);
    for (ll i = 0; i < n; i++) {
      cin >> airports[i].first >> airports[i].second;
      p[i] = polar_to_point(1,
              airports[i].first * M_PI / 180,
              airports[i].second * M_PI / 180);
    }
    double best = INF; int best_i = 0;
    for (ll i = 0; i < n; i++) {
      double t = 0;
      for (ll j = 0; j < n; j++) {
        t = max(t, acos(p[i] * p[j]));
      }
      if (t <= best || equal_double(t, best, 1e-6)) {
        best = t;
        best_i = i;
      }
    }
    cout << fixed << setprecision(2)
      << airports[best_i].first << " "
      << airports[best_i].second << endl;
  }
}
