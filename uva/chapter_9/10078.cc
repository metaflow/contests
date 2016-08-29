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
  ll x, y;
  point() {}
  point(ll x, ll y) : x(x), y(y) {}
  // scalar multiplication
  ll operator * (const point & o) {
    return x * o.x + y * o.y;
  }
  // vector multiplication
  ll operator ^ (const point & o) {
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

bool convex(vector<point> &p) {
  ll s = (p[1] - p[0]) ^ (p[2] - p[0]);
  for (ll i = 1; i < p.size(); i++) {
    int j = (i + 1) % p.size();
    int k = (j + 1) % p.size();
    if (s * ((p[j] - p[i]) ^ (p[k] - p[i])) < 0) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n, n) {
    vector<point> poly(n);
    for (ll i = 0; i < n; i++) cin >> poly[i].x >> poly[i].y;
    if (convex(poly)) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }
}
