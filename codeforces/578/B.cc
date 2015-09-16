#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
const l MAX = 200001;
const l MAXK = 11;

l DP[MAX][MAXK];

l dp(vl& a, l n, l k, l x) {
  if (n < 0) return 0;
  auto &r = DP[n][k];
  if (r != -1) return r;
  l t = a[n];
  r = 0;
  for (l i = 0; i <= k; i++) {
    r = max(r, t | dp(a, n - 1, k - i, x));
    t *= x;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k, x;
  while (cin >> n >> k >> x) {
    vl a(n);
    for (l i = 0; i < n; i++) cin >> a[i];
    fill(&DP[0][0], &DP[MAX][0], -1);
    cout << dp(a, n - 1, k, x) << endl;
  }
}
