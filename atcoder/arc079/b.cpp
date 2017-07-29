#if defined(LOCAL)
#define PROBLEM_NAME "b"
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

void solve(istream& cin, ostream& cout) {
  l k;
  while (cin >> k) {
    l n = 50;
    vl v(n);
    F(i, 0, n) v[i] = n - i - 1;
    F(i, 0, n) v[i] += k / n;
    F(i, 0, k % n) v[i]++;
    cout << n << lf;
    F(i, 0, n) {
      if (i) cout << ' ';
      cout << v[i];
    }
    cout << lf;
  }
}

bool solution_checker(istream& input, istream& /* expected */,
                      istream& actual, ostream& out) {
  l k;
  while (input >> k) {
    l n; actual >> n;
    l a, b; actual >> a >> b;
    if (a > b) swap(a, b);
    l t = 0;
    while (b >= n) {
      b -= n;
      a++;
      if (a > b) swap(a, b);
      t++;
    }
    if (k != t) {
      out << k << " <> " << t << endl;
      return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
#else
  solve(cin, cout);
#endif
}
