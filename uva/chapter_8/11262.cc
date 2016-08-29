#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();

struct point {
  double x, y;
  point() {}
  point(double x, double y) : x(x), y(y) {}
  double operator * (const point & o) {
    return x * o.x + y * o.y;
  }
  point operator - (const point& o) {
    return point(x - o.x, y - o.y);
  }
  point operator + (const point& o) {
    return point(x + o.x, y + o.y);
  }
  double operator >> (const point& o) {
    point d = (*this - o);
    return sqrt(d * d);
  }
};

ostream& operator << (ostream& s, const point& p) {
  s << "(" << p.x << ", " << p.y << ")";
  return s;
}

bool bipartite_matching_connect(const int u, vvb& m, vi& to, vb& used) {
  for (size_t v = 0; v < to.size(); v++) {
    if (!m[u][v] || used[v]) continue;
    used[v] = true;
    if (to[v] == -1 || bipartite_matching_connect(to[v], m, to, used)) {
      to[v] = u;
      return true;
    }
  }
  return false;
}

// {A} => {B}, m[i][j] == A[i] -> B[j]
int bipartite_matching(vvb& m) {
  if (m.empty()) return 0;
  vi to(m[0].size(), -1);
  int result = 0;
  for (size_t u = 0; u < m.size(); u++) {
    vb used(to.size());
    if (bipartite_matching_connect(u, m, to, used)) result++;
  }
  return result;
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
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n, k;
    cin >> n >> k;
    vector<point> red, blue;
    for (int i = 0; i < n; i++) {
      string color; int x, y;
      cin >> x >> y >> color;
      if (color == "red") {
        red.emplace_back(x, y);
      } else {
        blue.emplace_back(x, y);
      }
    }

    vvd d(red.size());
    for (size_t i = 0; i < red.size(); i++) {
      for (size_t j = 0; j < blue.size(); j++) {
        d[i].emplace_back(red[i] >> blue[j]);
      }
    }

    vvb allowed(red.size());
    for (auto &a : allowed) a.resize(blue.size());

    auto test = [&] (ll x) {
      for (size_t i = 0; i < d.size(); i++) {
        for (size_t j = 0; j < d[0].size(); j++) {
          allowed[i][j] = d[i][j] <= x;
        }
      }
      return bipartite_matching(allowed) >= k;
    };

    if (!test(3000)) {
      cout << "Impossible" << endl;
    } else {
      ll answer = binary_search_lower(-1, 3000, test);
      cout << answer << endl;
    }
  }
}
