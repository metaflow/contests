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

struct disjoint_set {
  vll parent;
  disjoint_set(size_t n) {
    parent.resize(n);
    for (size_t i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  ll get_parent(ll i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
  bool connected(ll i, ll j) {
    return get_parent(i) == get_parent(j);
  }
  void connect(ll i, ll j) {
    ll a = get_parent(i);
    ll b = get_parent(j);
    parent[a] = b;
  }
};

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
    ll n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<point> doctors(m);
    for (ll i = 0; i < m; i++) {
      cin >> doctors[i].x >> doctors[i].y;
    }
    vector<vector<point>> trees(n);
    for (ll i = 0; i < n; i++) {
      ll b; cin >> b;
      trees[i].resize(b);
      for (ll j = 0; j < b; j++) {
        cin >> trees[i][j].x >> trees[i][j].y;
      }
    }
    disjoint_set u(n);
    for (ll i = 0; i < n; i++) {
      for (ll j = i + 1; j < n; j++) {
        for (auto a : trees[i]) {
          for (auto b : trees[j]) {
            auto t = (a - b);
            if ((t * t) > (k * k)) continue;
            u.connect(i, j);
            break;
          }
          if (u.connected(i, j)) break;
        }
      }
    }
    bool ok = false;
    for (auto a : doctors) {
      for (ll i = 0; i < n; i++) {
        if (!u.connected(0, i)) continue;
        for (auto b : trees[i]) {
          auto t = a - b;
          if ((t * t) > (d * d)) continue;
          ok = true;
          break;
        }
        if (ok) break;
      }
      if (ok) break;
    }
    if (ok) {
      cout << "Tree can be saved :)" << endl;
    } else {
      cout << "Tree can't be saved :(" << endl;
    }
  }
}
