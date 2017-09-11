#if defined(LOCAL)
#define PROBLEM_NAME "gcd-rebuild"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
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

l gcd(l a, l b) {
  while (b) { l t = b; b = a % b; a = t; }
  return a;
}

l lcm(l a, l b) { return a * b / gcd(a, b); }


void solve(istream& cin, ostream& cout) {
  l n, m; cin >> n >> m;
  vl v(n, 1), u(m, 1);
  vvl g(n, vl(m));
  F(i, 0, n) F(j, 0, m) cin >> g[i][j];
  F(i, 0, n) F(j, 0, m) {
    v[i] = lcm(v[i], g[i][j]);
    u[j] = lcm(u[j], g[i][j]);
  }
  bool ok = true;
  F(i, 0, n) ok = ok and v[i] <= e9;
  F(i, 0, m) ok = ok and u[i] <= e9;
  F(i, 0, n) F(j, 0, m) ok = ok and gcd(v[i], u[j]) == g[i][j];
  if (not ok) { cout << -1 << lf; return; }
  F(i, 0, n) {
    if (i) cout << ' ';
    cout << v[i];
  }
  cout << lf;
  F(i, 0, m) {
    if (i) cout << ' ';
    cout << u[i];
  }
  cout << lf;
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
