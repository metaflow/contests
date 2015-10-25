#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long; using ll = pair<l, l>; using vll = vector<ll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
const l MOD = e9 + 7;

l add(l a, l b) {
  return (a + b) % MOD;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, w, k;
  while (cin >> n >> w >> k) {
    vl a(n), p(n);
    for (l i = 0; i < n; i++) cin >> a[i];
    vl s = a;
    sort(s.begin(), s.end());
    vll q;
    l i = 0;
    while (i < n) {
      l t = s[i];
      l c = 1;
      i++;
      while (i < n && s[i] == t) {c++; i++; }
      q.emplace_back(t, c);
    }
    l m = q.size();
    vvl dp(k + 1, vl(m));
    for (l i = 0; i < m; i++) dp[0][i] = 1;
    for (l i = 1; i <= k; i++) {
      for (l j = 0; j < m; j++) {
        dp[i][j] = add(dp[i][j], q[j].second * dp[i - 1][j]);
        if (j) dp[i][j] = add(dp[i][j], dp[i][j - 1]);
      }
    }
    l answer = 0;
    // not including tail
    l pieces = w / n;
    for (l x = 1; x <= k; x++) {
      answer = add(answer, (max(l(0), pieces - x + 1) % MOD) * dp[x][m - 1]);
    }
    // ends on tail
    for (l i = 0; i < w % n; i++) {
      auto it = lower_bound(q.begin(), q.end(), ll(a[i], 0));
      for (l x = 0; x <= k - 1 && x <= pieces; x++) {
        answer = add(answer, dp[x][it - q.begin()]);
      }
    }
    cout << answer << endl;
  }
}
