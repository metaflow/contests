#if defined(LOCAL)
#define PROBLEM_NAME "b"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define C(x, ...) ;
#include <bits/stdc++.h>
#endif

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

void solve(istream& cin, ostream& cout) {
  l n, c; cin >> n >> c;
  vl v(n), d(n);
  F(i, 0, n) cin >> d[i] >> v[i];
  vl ff(n), rr(n);
  l s = 0;
  F(i, 0, n - 1) {
    s += v[i];
    ff[i + 1] = max(ff[i], s - 2 * d[i]);
  }
  s = 0;
  B(i, 0, n - 1) {
    s += v[i + 1];
    rr[i] = max(rr[i + 1], s - 2 * (c - d[i + 1]));
  }
  l ans = 0;
  s = 0;
  F(i, 0, n) {
    s += v[i];
    ans = max(ans, s - d[i] + rr[i]);
  }
  s = 0;
  B(i, 0, n) {
    s += v[i];
    ans = max(ans, s - (c - d[i]) + ff[i]);
  }
  cout << ans << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
