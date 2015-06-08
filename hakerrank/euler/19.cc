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

ll days_in(ll y, ll m) {
  const int d[] {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (m != 2) return d[m];
  if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) return d[2] + 1;
  return d[2];
}

ll absolute_days(ll y, ll m, ll d) {
  y--;
  ll t = y * 365;
  t += y / 4 - y / 100 + y / 400;
  y++;
  m--;
  while (m > 0) {
    t += days_in(y, m);
    m--;
  }
  t += d - 1;
  return t;
}

int main() {
  // ll dow = (absolute_days(3059, 12, 9) - absolute_days(1900, 1, 1)) % 7;
  // cerr << dow << endl; return 0;
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll y1, m1, d1, y2, m2, d2;
    cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
    if (d1 > 1) {
      m1++;
      if (m1 > 12) {
        m1 = 1;
        y1++;
      }
    }
    d1 = d2 = 1;
    ll answer = 0;
    ll dow = (absolute_days(y1, m1, d1) - absolute_days(1900, 1, 1)) % 7;
    while (!((y1 > y2) || (y1 == y2 && m1 > m2))) {
      if (dow == 6) answer++;
      dow = (dow + days_in(y1, m1)) % 7;
      m1++;
      if (m1 > 12) {
        m1 = 1;
        y1++;
      }
    }
    cout << answer << endl;
  }
}
