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

const int MAX = 5000000;
int DP[MAX];

ll f(ll n) {
  if (n % 2 == 0) return n / 2;
  ll t = 3 * n + 1;
  assert(t > n);
  return t;
}

int dp(ll n) {
  if (n >= MAX) return dp(f(n)) + 1;
  int &r = DP[n];
  if (r == 0) r = 1 + dp(f(n));
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  fill_n(DP, MAX, 0);
  DP[1] = 1;
  int m = 1;
  vi a(MAX + 1);
  for (int ii = 1; ii <= MAX; ii++) {
    if (dp(ii) >= dp(m)) m = ii;
    a[ii] = m;
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << a[n] << endl;
  }
}
