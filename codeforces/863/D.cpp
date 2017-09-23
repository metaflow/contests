#if defined(LOCAL)
#define PROBLEM_NAME "D"
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

void solve(istream& cin, ostream& cout) {
  l n, q, m; cin >> n >> q >> m;
  vl v(n); F(i, 0, n) cin >> v[i];
  vector<tuple<l,l,l>> op(q);
  F(i, 0, q) cin >> get<0>(op[i]) >> get<1>(op[i]) >> get<2>(op[i]);
  reverse(all(op));
  vl p(m);
  F(i, 0, m) cin >> p[i];
  for (auto w : op) {
    l a, b, c; tie(c, a, b) = w;
    if (c == 1) {
      F(i, 0, m) {
        if (p[i] < a or p[i] > b) continue;
        p[i]--;
        if (p[i] < a) p[i] = b;
      }
    } else {
      F(i, 0, m) {
        if (p[i] < a or p[i] > b) continue;
        p[i] = b - (p[i] - a);
      }
    }
  }
  F(i, 0, m) {
    if (i) cout << ' ';
    cout << v[p[i] - 1];
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
