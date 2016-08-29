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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  const double R = 6378;
  map<string, point> cities;
  string city;
  while (cin >> city, city != "#") {
    double la, lo;
    cin >> la >> lo;
    la = (la * M_PI) / 180;
    lo = (lo * M_PI) / 180;
    cities[city] = polar_to_point(1, la, lo);
  }
  string a, b;
  while (cin >> a >> b, a != "#") {
    cout << a << " - " << b << endl;
    if (cities.count(a) * cities.count(b) == 0) {
      cout << "Unknown" << endl;
    } else {
      double t = cities[a] * cities[b];
      // cout << t << endl;
      if (t > 1) t = 1;
      if (t < -1) t = -1;
      double g = acos(t);
      cout << round(R * g) << " km" << endl;
    }
  }
}
