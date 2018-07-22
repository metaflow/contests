#if defined(LOCAL)
#define PROBLEM_NAME "a"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
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
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7;

l dp(l i, l j, l k, auto& w) {
  if (i >= w.size() || i < 0 || j >= w[i].size() || j < 0 || k >= w[i][j].size()
      || k < 0) return 0;
  auto& z = w[i][j][k];
  if (z == -1) {
    z = 0;
    if (k == 0) {
      z = (dp(i, j - 1, 2, w) + dp(i, j + 1, 1, w)) % MOD;
    } else {
      z = dp(i + 1, j, 0, w);
    }
  }
  return z;
}

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    cout << "Case #" << tc << ": ";
    l n; cin >> n;
    VVVL(w, n, 3, 3, -1);
    w[n - 1][2][1] = 1;
    string s;
    F(j, 0, 3) {
      cin >> s;
      F(i, 0, n) {
        if (s[i] == '.') continue;
        F(k, 0, 3) w[i][j][k] = 0;
      }
    }
    cout << dp(0, 0, 0, w) << lf;
  }
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
