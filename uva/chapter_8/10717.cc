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
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()

ll gcd(ll a, ll b) {
  while (b) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

int main() {
  // int a, b;
  // a = 1; b = 2;
  // tie(a, b) = make_pair(b, a);
  // cout << a << " " << b << endl;
  // return 0;

  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, t;
  while (cin >> n >> t, n) {
    vll coins(n);
    for (ll i = 0; i < n; i++) cin >> coins[i];
    vll tables(t);
    for (ll i = 0; i < t; i++) cin >> tables[i];
    vll lower(t, -1), upper(t, INF);
    for (ll a = 0; a < n; a++) {
      for (ll b = a + 1; b < n; b++) {
        ll ab = lcm(coins[a], coins[b]);
        for (ll c = b + 1; c < n; c++) {
          ll abc = lcm(ab, coins[c]);
          for (ll d = c + 1; d < n; d++) {
            ll all = lcm(abc, coins[d]);
            for (ll i = 0; i < t; i++) {
              ll k = tables[i] / all;
              ll l = k * all;
              ll u = l;
              if (u < tables[i]) u += all;
              lower[i] = max(lower[i], l);
              upper[i] = min(upper[i], u);
            }
          }
        }
      }
    }
    for (ll i = 0; i < t; i++) {
      cout << lower[i] << " " << upper[i] << endl;
    }
  }
}
