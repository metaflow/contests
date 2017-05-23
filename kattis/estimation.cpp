#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n, k;
  cin >> n >> k;
  vl v(n); F(i, 0, n) cin >> v[i];
  vvl cost(n, vl(n));
  F(i, 0, n) {
    priority_queue<l> lower;
    priority_queue<l, vl, greater<l>> upper;
    l sum_lower = 0, sum_upper = 0;
    F(j, i, n) {
      lower.emplace(v[j]);
      sum_lower += v[j];
      if (lower.size() > upper.size() + 1 or
          (not upper.empty() and upper.top() < lower.top())) {
        l x = lower.top();
        lower.pop();
        upper.emplace(x);
        sum_lower -= x;
        sum_upper += x;
      }
      if (upper.size() > lower.size()) {
        l x = upper.top();
        upper.pop();
        lower.emplace(x);
        sum_upper -= x;
        sum_lower += x;
      }
      l median = lower.top();
      cost[i][j] = (lower.size() * median - sum_lower) +
        (sum_upper - upper.size() * median);
    }
  }
  vl dp(n + 1, INF);
  dp[0] = 0;
  F(m, 0, k) B(i, n - 1, -1) F(j, i, n)
    dp[j + 1] = min(dp[j + 1], dp[i] + cost[i][j]);
  cout << dp[n] << lf;
}
