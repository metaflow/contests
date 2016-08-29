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

struct node {
  point p;
  vll distances;
  bool visited;
};

ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}

// invariant: answer is within (a, b], f(a) = false, f(b) = true
ll binary_search_lower(ll a, ll b, function<bool(ll)> f) {
  while (b - a > 1) {
    ll m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll l, w, n; cin >> l >> w >> n;
    vector<node> v(n + 2);
    for (ll i = 0; i < n + 2; i++) v[i].distances.resize(n + 2);
    for (ll i = 0; i < n; i++) cin >> v[i].p.x >> v[i].p.y;
    for (ll i = 0; i < n; i++) {
      for (ll j = i + 1; j < n; j++) {
        auto a = (v[i].p - v[j].p);
        v[i].distances[j] = v[j].distances[i] = a * a;
      }
      v[i].distances[n] = v[n].distances[i] = v[i].p.y * v[i].p.y;
      v[i].distances[n + 1] = v[n + 1].distances[i] =
        (w - v[i].p.y) * (w - v[i].p.y);
    }
    v[n].distances[n + 1] = v[n + 1].distances[n] = w * w;
    ll m = (w + 1) * (w + 1);
    ll answer = m - binary_search_lower(0, m, [&] (ll x) {
      ll r = m - x;
      for (auto &u : v) u.visited = false;
      queue<int> q;
      v[n].visited = true;
      q.emplace(n);
      while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (ll i = 0; i < n + 2; i++) {
          if (!v[i].visited && v[u].distances[i] < r) {
            v[i].visited = true;
            q.emplace(i);
          }
        }
      }
      return !v[n + 1].visited;
    });
    cout << "Maximum size in test case " << tc << " is "
         << fixed << setprecision(4) << sqrt(answer) << "." << endl;
  }
}
