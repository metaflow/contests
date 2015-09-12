// time: 13:00
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
const int MAX = 5001;

ll D[MAX][MAX];

ll dp(vll& v, ll pos, ll k, ll m) {
  if (k == 0) return 0;
  if (pos <= 0) return -INF;
  auto &d = D[pos][k];
  if (d != -1) return d;
  d = dp(v, pos - 1, k, m);
  ll sum = 0;
  for (ll i = 1; (i <= m) && (pos - i >= 0); i++) {
    sum += v[pos - i];
    d = max(d, sum + dp(v, pos - i, k - 1, m));
  }
  return d;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m, k;
  while (cin >> n >> m >> k) {
    fill(&D[0][0], &D[MAX][0], -1);
    vll v(n);
    for (ll i = 0; i < n; i++) {
      cin >> v[i];
    }
    cout << dp(v, n, k, m) << endl;
  }
}
