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

double grad_to_rad(double grad) {
  return grad * M_PI / 180;
}

double acos_(double v) {
  if (v > 1) v = 1;
  if (v < -1) v = -1;
  return acos(v);
}

const double R = 6371009;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    double lat_a, lat_b, long_a, long_b;
    cin >> lat_a >> long_a >> lat_b >> long_b;
    auto a = polar_to_point(1, grad_to_rad(lat_a), grad_to_rad(long_a));
    auto b = polar_to_point(1, grad_to_rad(lat_b), grad_to_rad(long_b));
    double t = (acos_(a * b) - (a >> b)) * R;
    cout << ll(round(t)) << endl;
  }
}
