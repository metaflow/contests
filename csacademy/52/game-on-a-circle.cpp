#if defined(LOCAL)
#define PROBLEM_NAME "game-on-a-circle"
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

l ask(l i) {
  cout << ((i + 100) % 100) << endl;
  cin >> i;
  return i;
}

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  while (tcc--) {
    if (ask(10)) {
      if (ask(21)) {
        // pick any 9 outside of this range
        l k = 50;
        F(i, 0, 9) {
          k++;
          while (k % 10 < 2) k++;
          ask(k);
        }
      } else {
        F(i, 0, 9) ask(31 + i * 10);
      }
    } else {
      l i = 9;
      while (i > 0) if (ask(i--)) break;
      if (i == 0) {
        ask(11);
      } else {
        if (ask(i--)) {
          while (i >= 0) {
            ask(20 + 10 * i);
            i--;
          }
        } else {
          while (i > 0) if (ask(i--)) break;
          while (i >= 0) {
            ask(20 + 10 * i);
            i--;
          }
        }
      }
    }
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
