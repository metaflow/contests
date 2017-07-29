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

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

const l MAX = e5 + 1;

void solve(istream& cin, ostream& cout) {
  //      0, 1, 2, 3, 4, 5, 6, 7
  vl b = {1, 1, 1, 7, 4, 2, 0, 8};
  vl digits(MAX, e6), value(MAX, -1), jump(MAX, -1);
  digits[0] = 0;
  F(i, 0, MAX) {
    F(j, 2, 8) {
      if (i + j >= MAX) break;
      if ((digits[i + j] > digits[i] + 1) or
          (digits[i + j] == digits[i] + 1 and value[i + j] > b[j])) {
        digits[i + j] = digits[i] + 1;
        value[i + j] = b[j];
        jump[i + j] = j;
      }
    }
  }
  l n;
  while (cin >> n) {
    L(n);
    if (n == 1) {
      cout << -1 << lf;
      continue;
    }
    if (n == 6) {
      cout << 0 << lf;
      continue;
    }
    l start = 2;
    F(j, 2, 8) {
      if (n - j < 0) break;
      l bj = j == 6 ? 6 : b[j];
      l bs = start == 6 ? 6 : b[start];
      if (digits[n - j] < digits[n - start] or
          (digits[n - j] == digits[n - start] and bj < bs))
        start = j;
    }
    cout << (start == 6 ? 6 : b[start]);
    n -= start;
    while (n) {
      cout << value[n];
      n -= jump[n];
    }
    cout << lf;
  }
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
