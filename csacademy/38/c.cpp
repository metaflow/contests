#if defined(LOCAL)
#define PROBLEM_NAME "c"
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

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

bool good(l i, vl& v, l k) {
  return (i == 0 or abs(v[i - 1] - v[i]) <= k)
    and (i + 1 >= v.size() or abs(v[i + 1] - v[i]) <= k);
}

void solve(istream& cin, ostream& cout) {
  l n, k;
  cin >> n >> k;
  vl v(n);
  F(i, 0, n) cin >> v[i];
  vl bad;
  F(i, 0, n) if (not good(i, v, k)) {
    bad.emplace_back(i);
  }
  if (bad.empty()) {
    cout << 0 << lf;
    return;
  }
  if (bad.size() > 6) {
    cout << -1 << lf;
    return;
  }
  for (auto x : bad) {
    F(i, 0, n) {
      swap(v[i], v[x]);
      bool ok = good(i, v, k);
      for (auto t : bad) ok = ok and good(t, v, k);
      if (ok) {
        cout << x + 1 << ' ' << i + 1 << lf;
        return;
      }
      swap(v[i], v[x]);
    }
  }
  cout << -1 << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
#else
  solve(cin, cout);
#endif
}
