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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int m; cin >> m;
    vd r(m);
    vi p(m);
    for (ll i = 0; i < m; i++) {
      cin >> r[i];
      p[i] = i;
    }
    double best = INF;
    while (true) {
      double border = 0;
      vd x(m);
      for (ll i = 0; i < m; i++) {
        double &ri = r[p[i]];
        x[i] = ri;
        for (ll j = 0; j < i; j++) {
          double &rj = r[p[j]];
          double a = x[j] + pow(pow(ri + rj, 2) - pow(ri - rj, 2) , 0.5);
          x[i] = max(x[i], a);
        }
        border = max(border, x[i] + ri);
      }
      best = min(best, border);
      if (!next_permutation(p.begin(), p.end())) break;
    }
    cout << fixed << setprecision(3) << best << endl;
  }
}
