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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-6;

struct line {
  ll x, s, y;
  ll id, pos;
};

struct event {
  ll a, b, query_no, query_pos;
  double t;
  ll type; // 0 - crossing, 1 - query
};

bool equal_double(double x, double y) {
  if (abs(x - y) < EPS) return true;
  // Is x or y too close to zero?
  if (abs(x) < EPS || abs(y) < EPS) return false;
  // Check relative precision.
  return (abs((x - y) / x) < EPS) && (abs((x - y) / y) < EPS);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    vector<line> v(n);
    for (ll i = 0; i < n; i++) {
      cin >> v[i].s >> v[i].x;
      v[i].id = i + 1;
    }
    ll m; cin >> m;
    for (ll i = 0; i < m; i++) {
      ll t; ll k;
      cin >> t >> k;
      for (auto &l : v) l.y = l.s * t + l.x;
      sort(v.begin(), v.end(),
        [] (const line& a, const line& b) {
          if (a.y != b.y) return a.y > b.y;
          return a.id < b.id;
        });
      cout << v[k - 1].id << endl;
    }
  }
}
