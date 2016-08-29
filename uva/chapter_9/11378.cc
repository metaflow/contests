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

ll solve(ll f, ll t, vector<point>& p) {
  if (t - f <= 1) return INF;
  ll m = (t + f) / 2;
  ll d = min(solve(f, m, p), solve(m, t, p));
  vi L, R;
  for (ll i = f; i < m; i++) L.emplace_back(i);
  for (ll i = m; i < t; i++) R.emplace_back(i);
  auto compare_y = [&] (const int a, const int b) {
    return p[a].y < p[b].y;
  };
  sort(L.begin(), L.end(), compare_y);
  sort(R.begin(), R.end(), compare_y);
  auto r = R.begin();
  for (auto l : L) {
    while (r != R.end() && p[*r].y < p[l].y - d) r++;
    auto t = r;
    while (t != R.end() && p[*t].y <= p[l].y + d) {
      ll dx = abs(p[*t].x - p[l].x);
      ll dy = abs(p[*t].y - p[l].y);
      d = min(d, max(dx, dy));
      t++;
    }
  }
  return d;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vector<point> p(n);
    for (ll i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    cout << solve(0, n, p) << endl;
  }
}
