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
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vll v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    ll l = v[0], r = v.back();
    for (ll i = 0; i < n; i++) {
      ll top = max(v[i] - l, r - v[i]);
      ll bot = INF;
      if (i > 0) bot = min(bot, v[i] - v[i - 1]);
      if (i < n - 1) bot = min(bot, v[i + 1] - v[i]);
      cout << bot << " " << top << endl;
    }
  }
}

