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

ll n, b1, b2;
const int MAX = 100;
using dps = tuple<int, int, int, double>;
dps DP[MAX][MAX][4];

dps dp(int p1, int p2, int mask, vector<point>& o) {
  dps &r = DP[p1][p2][mask];
  if (get<3>(r) < 0) {
    int next = max(p1, p2) + 1;
    if (next == n - 1) {
      r = make_tuple(0, 0, 0, (o[p1] >> o[next]) + (o[p2] >> o[next]));
      return r;
    }
    get<3>(r) = INF;
    bool special = (next == b1 || next == b2);
    if (!special || (mask & 0b01)) {
      double t = (o[p1] >> o[next]);
      int m = mask; if (special) m = m ^ 0b01;
      t += get<3>(dp(next, p2, m, o));
      if (t < get<3>(r)) {
        get<0>(r) = next;
        get<1>(r) = p2;
        get<2>(r) = m;
        get<3>(r) = t;
      }
    }
    if (!special || (mask & 0b10)) {
      double t = (o[p2] >> o[next]);
      int m = mask; if (special) m = m ^ 0b10;
      t += get<3>(dp(p1, next, m, o));
      if (t < get<3>(r)) {
        get<0>(r) = p1;
        get<1>(r) = next;
        get<2>(r) = m;
        get<3>(r) = t;
      }
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll tc = 0;
  while (cin >> n >> b1 >> b2, n) {
    tc++;
    vector<point> o(n);
    for (ll i = 0; i < n; i++) cin >> o[i].x >> o[i].y;
    fill(&DP[0][0][0], &DP[MAX][0][0], make_tuple(0, 0, 0, -1));
    auto a = dp(0, 0, 3, o);
    vll p1, p2;
    p1.emplace_back(0);
    p2.emplace_back(0);
    while (get<0>(a) + get<1>(a) != 0) {
      if (get<0>(a) != p1.back()) {
        p1.emplace_back(get<0>(a));
      } else {
        p2.emplace_back(get<1>(a));
      }
      a = dp(get<0>(a), get<1>(a), get<2>(a), o);
    }
    if (p1[1] != 1) swap(p1, p2);
    p1.emplace_back(n - 1);
    while (!p2.empty()) {
      p1.emplace_back(p2.back());
      p2.pop_back();
    }
    cout << "Case " << tc << ": "
    << fixed << setprecision(2) << get<3>(dp(0, 0, 3, o)) << endl;
    for (ll i = 0; i < p1.size(); i++) {
      if (i) cout << " ";
      cout << p1[i];
    }
    cout << endl;
  }
}
