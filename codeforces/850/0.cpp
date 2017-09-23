#if defined(LOCAL)
#define PROBLEM_NAME "0"
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

l mult(vl a, vl b) {
  l m = 0;
  F(i, 0, 5) m += a[i] * b[i];
  return m;
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  vvl v(n, vl(5));
  F(i, 0, n) F(j, 0, 5) cin >> v[i][j];
  if (n > 100) {
    cout << 0 << lf;
    return;
  }
  vl answer;
  F(i, 0, n) {
    bool ok = true;
    F(j, 0, n) F(k, 0, n) {
      if (i == j or j == k or i == k) continue;
      vl a(5), b(5);
      F(m, 0, 5) {
        a[m] = v[j][m] - v[i][m];
        b[m] = v[k][m] - v[i][m];
      }
      if (mult(a, b) > 0) ok = false;
    }
    if (ok) answer.emplace_back(i + 1);
  }
  cout << answer.size() << lf;
  for (auto i : answer) cout << i << lf;
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
