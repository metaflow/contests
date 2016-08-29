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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << "Data set #" << tc << " contains ";
    set<point> uniq;
    for (ll i = 0; i < n; i++) {
      point a;
      double x, y;
      cin >> x >> y;
      uniq.emplace(round(x * 100), round(y * 100));
    }
    if (uniq.size() == 1) {
      cout << "a single gnu." << endl;
    } else {
      vector<point> v;
      for (auto e : uniq) v.emplace_back(e);
      n = v.size();
      int best = 0;
      for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
          int aligned = 2;
          point d = v[i] - v[j];
          for (ll k = j + 1; k < n; k++) {
            if ((d ^ (v[i] - v[k])) == 0) aligned++;
          }
          best = max(best, aligned);
        }
      }
      cout << n << " gnus, out of which a maximum of " << best
           << " are aligned." << endl;
    }
  }
}
