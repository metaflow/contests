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

vvd mdp;
ll n;
vector<point> dots;

double dp(int p1, int p2) {
  double &r = mdp[p1][p2];
  if (r < 0) {
    int v = max(p1, p2) + 1;
    if (v == n - 1) {
      r = (dots[p1] >> dots[v]) + (dots[p2] >> dots[v]);
      return r;
    }
    r = min((dots[p1] >> dots[v]) + dp(v, p2),
            (dots[p2] >> dots[v]) + dp(p1, v));
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  while (cin >> n) {
    dots.resize(n);
    mdp.clear(); mdp.resize(n);
    for (ll i = 0; i < n; i++) {
      cin >> dots[i].x >> dots[i].y;
      mdp[i].resize(n, -1);
    }
    cout << fixed << setprecision(2) << dp(0, 0) << endl;
  }
}
