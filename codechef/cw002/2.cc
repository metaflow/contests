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
const int MAX = 1001;

double dp[MAX][MAX];

// expected average for this configuration
double f(vd& v, vd& p, ll n, ll k) {
  auto &r = dp[n][k];
  if (r >= 0) return r;
  if (k == 0 || n == 0) return r = 0;
  // take
  double t = (double)k / (double)n;
  r = t * (v[n - 1] * p[k - 1] + f(v, p, n - 1, k - 1));
  // or not
  if (k != n) {
    r += (1 - t) * f(v, p, n - 1, k);
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, k; cin >> n >> k;
    fill(&dp[0][0], &dp[MAX][0], -1);
    vd v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    vd p(k);
    for (ll i = 0; i < k; i++) cin >> p[i];
    sort(v.begin(), v.end());
    sort(p.begin(), p.end());
    double a = f(v, p, n, k);
    cout << fixed << setprecision(3) << round(a * 10) / 1000 << endl;
  }
}
