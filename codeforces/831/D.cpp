#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "D"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

l N, K, D;

l dfs(l a, l b, vl& v, vl& u, vvl& dp) {
  if (a == -1) return 0;
  if (b == -1) return INF;
  l& r = dp[a][b];
  if (r == -1) {
    l cost = abs(v[a] - u[b]) + abs(u[b] - D);
    r = min(max(cost, dfs(a - 1, b - 1, v, u, dp)),
            dfs(a, b - 1, v, u, dp));
  }
  return r;
}

void solve(istream& cin, ostream& cout) {
  while (cin >> N >> K >> D) {
    vl v(N); F(i, 0, N) cin >> v[i];
    vl u(K); F(i, 0, K) cin >> u[i];
    sort(all(v));
    sort(all(u));
    vvl dp(N, vl(K, -1));
    cout << dfs(N - 1, K - 1, v, u, dp) << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
