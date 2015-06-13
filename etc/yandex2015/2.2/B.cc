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

struct car {
  int a, b, v;
};

int main() {
  // ios_base::sync_with_stdio(false); cin.tie(0);
  int n;
  while (cin >> n) {
    vector<car> v(n);
    vector<pair<double, double>> intervals;
    for (ll i = 0; i < n; i++) {
      cin >> v[i].a >> v[i].b >> v[i].v;
    }
    for (ll i = 0; i < n; i++) {
      auto c1 = v[i];
      for (ll j = 0; j < n; j++) {
        auto c2 = v[j];
        if (c1.v > c2.v) continue;
        if (c1.v == c2.v) {
          if (c1.b <= c2.a || c2.b <= c1.a) {
            intervals.emplace_back(0, 0);
          }
          continue;
        }
        double t_meet = double(c1.a - c2.b + 1) / double(c2.v - c1.v);
        t_meet = max(0.0, t_meet);
        double t_out = double(c1.b - c2.a) / double(c2.v - c1.v);
        if (t_out < 0) {
          t_out = t_meet;
        }
        // cerr << t_meet << ".." << t_out << endl;
        intervals.emplace_back(t_meet, t_out);
      }
    }
    auto f = intervals[0];
    for (auto e : intervals) {
      f.first = max(f.first, e.first);
      f.second = min(f.second, e.second);
    }
    printf("%.7f\n", f.second - f.first);
  }
}
