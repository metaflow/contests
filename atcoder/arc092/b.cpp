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
  l n; cin >> n;
  vl a(n), b(n);
  F(i, 0, n) cin >> a[i];
  F(i, 0, n) cin >> b[i];
  vl s(n);
  l answer = 0;
  F(k, 0, 29) {
    l a1 = 0, b1 = 0;
    F(i, 0, n) a1 += (a[i] >> k) & 1;
    F(i, 0, n) b1 += (b[i] >> k) & 1;
    l t = a1 * (n - b1) + b1 * (n - a1);
    l q = l(1) << k;
    l m = q - 1;
    for (l i : b) {
      auto p = lower_bound(all(s), q - (i & m));
      t += distance(p, s.end());
    }
    answer += (t % 2) << k;
    m = (l(1) << (k + 1)) - 1;
    F(i, 0, n) s[i] = a[i] & m;
    sort(all(s));
  }
  cout << answer << lf;
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
