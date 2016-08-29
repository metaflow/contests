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

struct point {ll x, y;};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  ll tc = 0;
  while (cin >> n, n) {
    tc++;
    vector<point> v(n);
    for (ll i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    ll min_x = -INF, max_x = INF;
    ll min_y = -INF, max_y = INF;
    for (ll i = 0; i < n; i++) {
      ll j = (i + 1) % n;
      if (v[i].x == v[j].x) {
        if (v[i].y < v[j].y) {
          min_x = max(min_x, v[i].x);
        } else {
          max_x = min(max_x, v[i].x);
        }
      } else {
        if (v[i].x < v[j].x) {
          max_y = min(max_y, v[i].y);
        } else {
          min_y = max(min_y, v[i].y);
        }
      }
    }
    cout << "Floor #" << tc << endl;
    if (min_x <= max_x && min_y <= max_y) {
      cout << "Surveillance is possible." << endl;
    } else {
      cout << "Surveillance is impossible." << endl;
    }
    cout << endl;
  }
}
