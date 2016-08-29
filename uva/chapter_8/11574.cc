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
  double x, y;
  point() {}
  point(double x, double y) : x(x), y(y) {}
  // scalar multiplication
  double operator * (const point & o) {
    return x * o.x + y * o.y;
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

struct boat {
  point coord;
  point speed;
};

// real roots of axx + bx + c = 0
vd quadratic_equation(double a, double b, double c) {
  vd _;
  double d = b * b - 4 * a * c;
  if (d < 0) return _;
  d = sqrt(d);
  double x1 = (-b - d) / 2 / a;
  double x2 = (-b + d) / 2 / a;
  _.emplace_back(x1);
  if (x2 != x1) _.emplace_back(x2);
  return _;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    double r;
    int n;
    cin >> n >> r;
    vector<boat> fleet(n);
    for (ll i = 0; i < n; i++) {
      double x, y, d, s;
      cin >> x >> y >> d >> s;
      d = d * M_PI / 180;
      fleet[i].coord.x = x;
      fleet[i].coord.y = y;
      fleet[i].speed.x = s * sin(d);
      fleet[i].speed.y = s * cos(d);
      cerr << fleet[i].coord << " " << fleet[i].speed << endl;
    }
    double t = 1e10;
    for (ll i = 0; i < n; i++) {
      for (ll j = i + 1; j < n; j++) {
        point dc = fleet[i].coord - fleet[j].coord;
        point dv = fleet[i].speed - fleet[j].speed;
        if ((dc * dc) <= r * r) {
          t = 0;
          break;
        }
        auto roots = quadratic_equation(dv * dv,
                                        2 * (dv * dc),
                                        (dc * dc) - r * r);
        for (auto q : roots) if (q >= 0) t = min(t, q);
      }
    }
    if (t == 1e10) {
      cout << "No collision." << endl;
    } else {
      cout << round(t) << endl;
    }
  }
}
