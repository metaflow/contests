#include <bits/stdc++.h>

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
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l MOD = e9 + 7;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l N;
  while (cin >> N) {
    vl dp(N + 1);
    dp[0] = 1;
    dp[1] = N;
    l sum = N;
    F(x, 2, N + 1) {
      l& r = dp[x];
      r = ((N - 1) * (N - 1) + sum + N - x + 2 - dp[x - 2] + MOD) % MOD;
      sum = (sum + r) % MOD;
    }
    cout << dp[N] << '\n';
  }
}
